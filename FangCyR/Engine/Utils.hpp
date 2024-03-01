//
// Created by FangCybertron
//
#pragma once

#include <cstdint>
#include <link.h>
#include <sys/mman.h>
#include <vector>
#include <string>
#include "KittyMemory/KittyInclude.hpp"

static uintptr_t GetAddress = 0;

#define LogTag OBFUSCATE("FANG")
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, LogTag, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, LogTag, __VA_ARGS__))
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO,  LogTag, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN,  LogTag, __VA_ARGS__))

#define LibIl2cpp OBFUSCATE("libil2cpp.so")
#define LibLogic OBFUSCATE("liblogic.so")
#define LibUnity OBFUSCATE("libunity.so")
#define LibEgl OBFUSCATE("libEGL.so")

#if defined(__aarch64__)
#define SplitApk OBFUSCATE("split_config.arm64_v8a.apk")
#else
#define SplitApk OBFUSCATE("split_config.armeabi_v7a.apk")
#endif

#if defined(__aarch64__)
#define ABI  OBFUSCATE("[x64]")
#define ARCH OBFUSCATE("arm64-v8a")
#else
#define ABI  OBFUSCATE("[x32]")
#define ARCH OBFUSCATE("armeabi-v7a")
#endif

#if defined(__aarch64__)
#define RETURN OBFUSCATE("1F C0 03 5F D6")
#define TRUE   OBFUSCATE("20 00 80 D2 C0 03 5F D6")
#define FALSE  OBFUSCATE("00 00 80 D2 C0 03 5F D6")
#else
#define RETURN OBFUSCATE("1E FF 2F E1")
#define TRUE   OBFUSCATE("01 00 A0 E3 1E FF 2F E1")
#define FALSE  OBFUSCATE("00 00 A0 E3 1E FF 2F E1")
#endif

#define InitFunc(ret, args, void_ptr) reinterpret_cast<ret(*) args>(void_ptr)

void *fuzzy_search(void *thiz) {
    int fuzz[4096];
    while (1) {
        for (int i = 0; i < 4096; i++) {
            fuzz[i] = rand() % 4096;
        }
        sleep(1);
    }
    return nullptr;
}

static uintptr_t Offset(const char *Addr) {
    if (GetAddress == 0) {
        return 0;
    }
    return (reinterpret_cast<uintptr_t>(GetAddress + Tools::String2Offset(Addr)));
}

auto HOOK = [](auto ptr, auto newMethod, auto &&oldBytes) {
    if (Tools::IsPtrValid((void *)ptr)) {
        Tools::HookFunc((void *)ptr, (void *)newMethod, (void **) &oldBytes);
    }
    return nullptr;
};

auto HOOKSYM = [](auto img, auto sym, auto newMethod, auto &&oldBytes) {
    auto symbol = DobbySymbolResolver(img, sym);
    if (symbol != nullptr) {
        Tools::HookFunc((void *)symbol, (void *)newMethod, (void **) &oldBytes);
    }
    return nullptr;
};

typedef void (* ADBI)(RegisterContext *ctx, const HookEntryInfo *info);
auto ADBISYM = [](auto sym, ADBI hiject){
    //uintptr_t p_sym = ElfScanner::createWithPath(img).findSymbol(sym);
    auto addr = (uintptr_t)dlsym(RTLD_NEXT, sym);
    if((void *)addr != nullptr){
        DobbyInstrument((void *)addr, hiject);
    }
    return nullptr;
};

auto ADBIFUNC = [](auto addr, ADBI hiject){
    if (Tools::IsPtrValid((void *)addr)) {
        DobbyInstrument((void *)addr, hiject);
    }
    return nullptr;
};

float getFileSize(std::string filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        //std::cerr << "Gagal membuka file " << filename << std::endl;
        return 0.0f;
    }
    float size = static_cast<float>(file.tellg()) / 1024.0f;
    file.close();
    return size;
}

namespace RemapTools {
    struct ProcMapInfo {
        uintptr_t start;
        uintptr_t end;
        uintptr_t offset;
        uint8_t perms;
        ino_t inode;
        char* dev;
        char* path;
    };

    std::vector<ProcMapInfo> ListModulesWithName(std::string name) {
        std::vector<ProcMapInfo> returnVal;

        char buffer[512];
        FILE *fp = fopen("/proc/self/maps", "re");
        if (fp != nullptr) {
            while (fgets(buffer, sizeof(buffer), fp)) {
                if (strstr(buffer, name.c_str())) {
                    ProcMapInfo info{};
                    char perms[10];
                    char path[255];
                    char dev[25];

                    sscanf(buffer, "%lx-%lx %s %ld %s %ld %s", &info.start, &info.end, perms, &info.offset, dev, &info.inode, path);

                    //Process Perms
                    if (strchr(perms, 'r')) info.perms |= PROT_READ;
                    if (strchr(perms, 'w')) info.perms |= PROT_WRITE;
                    if (strchr(perms, 'x')) info.perms |= PROT_EXEC;
                    if (strchr(perms, 'r')) info.perms |= PROT_READ;

                    //Set all other information
                    info.dev = dev;
                    info.path = path;

                    LOGI("Line: %s", buffer);
                    returnVal.push_back(info);
                }
            }
        }
        return returnVal;
    }

    void RemapLibrary(std::string name) {
        std::vector<ProcMapInfo> maps = ListModulesWithName(name);

        for (ProcMapInfo info : maps) {
            void *address = (void *)info.start;
            size_t size = info.end - info.start;
            void *map = mmap(0, size, PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

            if ((info.perms & PROT_READ) == 0) {
                LOGI("Removing protection: %s", info.path);
                mprotect(address, size, PROT_READ);
            }

            if (map == nullptr) {
                LOGE("Failed to Allocate Memory: %s", strerror(errno));
            }
            LOGI("Allocated at address %p with size of %zu", map, size);

            //Copy to new location
            std::memmove(map, address, size);
            mremap(map, size, size, MREMAP_MAYMOVE | MREMAP_FIXED, info.start);

            //Reapply protection
            mprotect((void *)info.start, size, info.perms);
        }
    }
}