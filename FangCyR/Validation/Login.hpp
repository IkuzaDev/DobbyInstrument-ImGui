#pragma once

void *hack_thread(void *);
using json = nlohmann::json;
std::string g_Token, g_Auth;
static std::string expired = OBFUSCATE("");
static std::string title = OBFUSCATE("bakso kontol");
static std::string version = OBFUSCATE("Bakso Kontol");
static std::string battleData = OBFUSCATE("");

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *) userp;
    mem->memory = (char *) realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
        return 0;
    }
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}

std::string GetSerial(){
    JavaVM *vm = JavaVm;
    JNIEnv *env;
    vm->AttachCurrentThread(&env, 0);
    auto object = Context();
    std::string hwid = Tools::GetDeviceModel(env);
    return hwid;
    vm->DetachCurrentThread();
}

std::string Login(const char *user_key, bool *success) {
    JavaVM *vm = JavaVm;
    JNIEnv *env;
    vm->AttachCurrentThread(&env, 0);
    auto object = Context();
    std::string hwid = user_key;
    hwid += Tools::GetAndroidID(env, object);
    hwid += Tools::GetDeviceModel(env);
    hwid += Tools::GetDeviceBrand(env);
    std::string UUID = Tools::GetDeviceUniqueIdentifier(env, hwid.c_str());
    vm->DetachCurrentThread();
    std::string errMsg;

    struct MemoryStruct chunk {};
    chunk.memory = (char *) malloc(1);
    chunk.size = 0;

    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        //std::string URL_AUTH = OBFUSCATE("https://d5studio.my.id/");//ikuza
        //std::string URL_AUTH = OBFUSCATE("https://zeropremium.my.id/");//rian
        //std::string URL_AUTH = OBFUSCATE("https://xiveveyi.my.id/");//xiveveyi
        std::string URL_AUTH = OBFUSCATE("https://aira-store.my.id/");//aira
        if(URL_AUTH != DECODE(OBFUSCATE("aHR0cHM6Ly9haXJhLXN0b3JlLm15LmlkLw=="))){
            URL_AUTH = DECODE(OBFUSCATE("aHR0cHM6Ly9haXJhLXN0b3JlLm15LmlkLw=="));
        }
        curl_easy_setopt(curl, CURLOPT_URL, URL_AUTH.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, OBFUSCATE("Accept: application/json"));
        headers = curl_slist_append(headers, OBFUSCATE("Content-Type: application/x-www-form-urlencoded"));
        headers = curl_slist_append(headers, OBFUSCATE("Charset: UTF-8"));
        
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        char data[4096];
        sprintf(data, OBFUSCATE("game=MLBB&appVer=v2.1&user_key=%s&serial=%s"), user_key, UUID.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            try {
                json result = json::parse(chunk.memory);
                auto STATUS = std::string{OBFUSCATE("status")};
                if (result[STATUS] == true) {
                    auto DATA = std::string{OBFUSCATE("data")};
                    auto TOKEN = std::string{OBFUSCATE("token")};
                    auto RNG = std::string{OBFUSCATE("rng")};
                    auto EXPIRED = std::string{OBFUSCATE("DURASI")};
                    auto TITLE = std::string{OBFUSCATE("MOD_NAME")};
                    auto VERSION = std::string{OBFUSCATE("MOD_STATUS")};
                    auto BATTLEDATA = std::string{OBFUSCATE("btData")};
                    std::string token = result[DATA][TOKEN].get<std::string>();
                    time_t rng = result[DATA][RNG].get<time_t>();
                    expired = result[DATA][EXPIRED].get<std::string>();
                    title = "";
                    version = result[DATA][VERSION].get<std::string>();
                    battleData = "";
                    if (rng + 30 > time(0)) {
                        std::string auth = OBFUSCATE("MLBB");
                        auth += std::string(OBFUSCATE("-"));
                        auth += user_key;
                        auth += std::string(OBFUSCATE("-"));
                        auth += UUID;
                        auth += std::string(OBFUSCATE("-"));
                        auth += std::string(OBFUSCATE("Vm8Lk7Uj2JmsjCPVPVjrLa7zgfx3uz9E"));
                        std::string outputAuth = Tools::CalcMD5(auth);
                        g_Token = token;
                        g_Auth = outputAuth;
                        *success = g_Token == g_Auth;
                        if (success) {
                            pthread_t t;
                            pthread_create(&t, nullptr, hack_thread, nullptr);
                        }
                    } else {        
                        *success = false;
                        errMsg = std::string{OBFUSCATE("TIME ERROR!")};
                    }
                } else {
                    *success = false;
                    auto REASON = std::string{OBFUSCATE("reason")};
                    errMsg = result[REASON].get<std::string>();
                }
            } catch (json::exception &e) {
                
            }
        } else {
            *success = false;
            errMsg = std::string(curl_easy_strerror(res));
        }
    }
    curl_easy_cleanup(curl);
    return errMsg;
}

