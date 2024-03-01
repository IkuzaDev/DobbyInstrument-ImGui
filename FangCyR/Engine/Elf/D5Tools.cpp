//
// Created by Admin on 2/11/2024.
//

#include <elf.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
//#include <dlfcn.h>
#include <string>
#include <link.h>
#include "include/D5Tools.h"

#define TAG_NAME	"dlfcn"

#define log_info(fmt,args...) __android_log_print(ANDROID_LOG_ERROR, TAG_NAME, (const char *) fmt, ##args)
#define log_err(fmt,args...) __android_log_print(ANDROID_LOG_ERROR, TAG_NAME, (const char *) fmt, ##args)

#ifdef __arm__
#define Elf_Ehdr Elf32_Ehdr
#define Elf_Shdr Elf32_Shdr
#define Elf_Sym  Elf32_Sym
#elif defined(__aarch64__)
#define Elf_Ehdr Elf64_Ehdr
#define Elf_Shdr Elf64_Shdr
#define Elf_Sym  Elf64_Sym
#else
#error "Arch unknown, please port me"
#endif

struct context {
    void *load_address;
    void *dynstr;
    void *dynsym;
    int nsyms;
    off_t bias;
};

int ElfTools::d5close(void *handle) {
    if (handle) {
        context *ctx = static_cast<context*>(handle);
        if (ctx->dynsym)
            free(ctx->dynsym);
        if (ctx->dynstr)
            free(ctx->dynstr);
        free(ctx);
        return 1;
    }
    return 0;
}

/* flags are ignored */

void *ElfTools::d5open(const char *path, int flags) {
    FILE *maps;
    char buffer[256];
    bool found_lib = false;
    uintptr_t load_address = 0x0;
    int size = 0;
    ElfW(Ehdr) *elf = (decltype(elf)) MAP_FAILED;

    maps = fopen("/proc/self/maps", "r");
    if (!maps) {
        //log_err("fdlopen : failed to open lib by path");
        return nullptr;
    }

    while (!found_lib && fgets(buffer, sizeof(buffer), maps)) {
        if (strstr(buffer, path) && (strstr(buffer, "r-xp") || strstr(buffer, "r--p")))
            found_lib = true;
    }
    fclose(maps);

    if (!found_lib) {
        //log_err("fdlopen : failed to find lib");
        return nullptr;
    }

    if (sscanf(buffer, "%lx", &load_address) != 1) {
        //log_err("failed to read load address");
        return nullptr;
    }

    //log_info("%s loaded at 0x%08lx", path.c_str(), load_address);

    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        //log_err("failed to open %s", path.c_str());
        return nullptr;
    }

    size = lseek(fd, 0, SEEK_END);
    if (size <= 0) {
        //log_err("lseek failed");
        close(fd);
        return nullptr;
    }

    elf = (decltype(elf)) mmap(0, size, PROT_READ, MAP_SHARED, fd, 0);
    close(fd);

    if (elf == MAP_FAILED) {
        //log_err("failed to mmap");
        return nullptr;
    }

    context *ctx = static_cast<context *>(calloc(1, sizeof(context)));
    ctx->load_address = (void *) load_address;
    char *shoff = ((char *) elf) + elf->e_shoff;

    for (int i = 0; i < elf->e_shnum; i++, shoff += elf->e_shentsize) {
        ElfW(Shdr) *shdr = (decltype(shdr)) shoff;
        switch (shdr->sh_type) {
            case SHT_DYNSYM:
                ctx->dynsym = malloc(shdr->sh_size);
                memcpy(ctx->dynsym, ((char *)elf) + shdr->sh_offset, shdr->sh_size);
                ctx->nsyms = (shdr->sh_size / sizeof(ElfW(Sym)));
                break;

            case SHT_STRTAB:
                if (ctx->dynstr)
                    break;

                ctx->dynstr = malloc(shdr->sh_size);
                memcpy(ctx->dynstr, ((char *) elf) + shdr->sh_offset, shdr->sh_size);
                break;

            case SHT_PROGBITS:
                if (!ctx->dynstr || !ctx->dynsym)
                    break;

                ctx->bias = (off_t) shdr->sh_addr - (off_t) shdr->sh_offset;
                i = elf->e_shnum;
        }
    }

    munmap(elf, size);
    elf = nullptr;

    return ctx;
}

void *ElfTools::d5sym(void *handle, const char *name) {
    context *ctx = static_cast<context *>(handle);
    ElfW(Sym) *sym = (decltype(sym)) ctx->dynsym;
    char *strings = (char *) ctx->dynstr;
    int k = 0;

    for (k = 0; k < ctx->nsyms; k++, sym++)
        if (strstr(strings + sym->st_name, name) != 0) {
            void *ret = (char *) ctx->load_address + sym->st_value - ctx->bias;
            //log_info("%s found at %p", name.c_str(), ret);
            return ret;
        }
    return nullptr;
}