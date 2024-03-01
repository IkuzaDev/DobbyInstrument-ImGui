#include "Main.hpp"
//login by ID_games
static bool MyLOGIN;
static bool ProcLOGIN;

void InjectID(){
    if(SystemData::m_uiID() != 0 || SystemData::m_uiID() != NULL){
        Activated = GetGIDRegister(SystemData::m_uiID(), MyLOGIN);
    }
};

void *imgui_thread(void *thiz) {
    
    do {
        sleep(1);
    } while (!Tools::IsAddressLoaded(LibLogic));
    
    FangEngine::Il2CppFindSymbol();
    
    FangEngine::Il2CppThreadAttach();
    
    LoaderPrivate();
    
    auto libs_unity = KittyMemory::getMapsByName(LibUnity);
    //auto unityELF = ElfScanner::createWithPath(LibUnity);
    auto nativeInjectEvent_fn = KittyScanner::findRegisterNativeFnv2(libs_unity, OBFUSCATE("nativeInjectEvent"));
    if (!nativeInjectEvent_fn.isValid()) {
        libs_unity = KittyMemory::getMapsByName(SplitApk);
        //unityELF = ElfScanner::createWithPath(SplitApk);
        nativeInjectEvent_fn = KittyScanner::findRegisterNativeFnv2(libs_unity, OBFUSCATE("nativeInjectEvent"));
    }
    HOOK(nativeInjectEvent_fn.fnPtr, NativeInjectEvent, Orig_NativeInjectEvent);

    ADBISYM(OBFUSCATE("eglSwapBuffers"), eglSwapBuffers_handler);
    //HOOKSYM(LibEgl, OBFUSCATE("eglSwapBuffers"), EglSwapBuffers, Orig_EglSwapBuffers);

    FangEngine::Il2CppThreadDetach();
    pthread_exit(nullptr);
    return nullptr;
}

void *hack_thread(void *thiz) {
    
    while (!GetAddress) {
        GetAddress = Tools::GetBaseAddress(LibLogic);
        sleep(1);
    }
    
    FangEngine::Il2CppFindSymbol();
    
    FangEngine::Il2CppThreadAttach();
    
    LoaderPublic();
    //ADBIFUNC(Class::ShowSelfPlayer::OnUpdate, OnUpdate_handler);
    //ADBIFUNC(Class::ShowSelfPlayer::OnUpdate, OnUpdate_handler);
    //Tools::Hook((void *) Class::GameMain::PlugInTesting, (void *) PlugInTesting, (void **) &oPlugInTesting);
    //Tools::Hook((void *) Class::APKSignature::IsSignatureSame, (void *) IsSignatureSame, (void **) &oIsSignatureSame);

    FangEngine::Il2CppThreadDetach();
    //RemapTools::RemapLibrary("libdobby.so");
    CONFIG::LoginValid = true;
    pthread_exit(nullptr);
    return nullptr;
}

jint (JNICALL *Real_JNI_OnLoad)(JavaVM *vm, void *reserved);
JNIEXPORT jint JNICALL Call_JNI_OnLoad(JavaVM *vm, void *reserved) {
    
    std::string apkPkg = Tools::GetPackageName(Env(), Context());
    
    std::string libAkSound = std::string(OBFUSCATE("libAkSoundEngine.so"));
    std::string libNevada1 = std::string(OBFUSCATE("libD5.bytes"));
    std::string libNevada2 = std::string(OBFUSCATE("libD5.so"));
    
    std::string localPath = std::string(OBFUSCATE("/storage/emulated/0/Android/data/")) + apkPkg + std::string(OBFUSCATE("/files/dragon2017/assets/comlibs/")) + std::string(ARCH);
    std::string rootPath = std::string(OBFUSCATE("/data/data/")) + apkPkg + std::string(OBFUSCATE("/app_libs/comlibs/")) + std::string(ARCH);
    
    std::string pathAkSound = rootPath + std::string(OBFUSCATE("/")) + libAkSound;
    std::string pathNevada1 = localPath + std::string(OBFUSCATE("/")) + libNevada1;
    std::string pathNevada2 = rootPath + std::string(OBFUSCATE("/")) + libNevada2;
    std::string pathAkSoundMod = localPath + std::string(OBFUSCATE("/")) + std::string(OBFUSCATE("libAkSoundEngine.bytes"));
    
    if (CopyFile(pathNevada1.c_str(), pathNevada2.c_str())) {
        void *handle = dlopen(pathNevada2.c_str(), RTLD_NOW);
        if (!handle) {
            handle = dlopen(pathNevada2.c_str(), RTLD_NOW);
            sleep(1);
        }
        auto Hook_JNI_OnLoad = dlsym(handle, OBFUSCATE("JNI_OnLoad"));
        if (Hook_JNI_OnLoad) {
            Real_JNI_OnLoad = decltype(Real_JNI_OnLoad)(Hook_JNI_OnLoad);
            pthread_t t;
            pthread_create(&t, nullptr, imgui_thread, nullptr);
            pthread_create(&t, nullptr, fuzzy_search, nullptr);
            //dlclose(handle);
            if (CheckFile(pathNevada2.c_str())) {
                //loadLibrary("libD5.so");
                std::remove(pathAkSound.c_str());
                std::rename(pathNevada2.c_str(), pathAkSound.c_str());
                std::remove(pathAkSoundMod.c_str());
                std::remove(pathNevada2.c_str());
                std::rename(libNevada1.c_str(), pathAkSoundMod.c_str());
                //RemapTools::RemapLibrary(libNevada2);
            }
            return Real_JNI_OnLoad(vm, reserved);
        }

        SizeFile = getFileSize(pathAkSoundMod);
        auto *p_handler = dlopen(pathAkSound.c_str(), RTLD_NOW);
        if(!p_handler){
            p_handler = dlopen(pathAkSound.c_str(), RTLD_NOW);
        }else{
            RemapTools::RemapLibrary(libAkSound);
        }
    }
    return JNI_ERR;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JavaVm = vm;
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    return Call_JNI_OnLoad(vm, reserved);
}
