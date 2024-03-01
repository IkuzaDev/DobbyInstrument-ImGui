#pragma once

JavaVM *JavaVm;

static JNIEnv *Env() {
	JNIEnv *env;
	int status = JavaVm->GetEnv((void**)&env, JNI_VERSION_1_6);
	if(status < 0) {
		status = JavaVm->AttachCurrentThread(&env, NULL);
		if(status < 0) {
			return nullptr;
		}
	}
	return env;
}

static jobject Context() {
	JNIEnv *env = Env();
	jclass activityThread = env->FindClass(OBFUSCATE("android/app/ActivityThread"));
	jmethodID currentActivityThread = env->GetStaticMethodID(activityThread, OBFUSCATE("currentActivityThread"), OBFUSCATE("()Landroid/app/ActivityThread;"));
	jobject at = env->CallStaticObjectMethod(activityThread, currentActivityThread);
	jmethodID getApplication = env->GetMethodID(activityThread, OBFUSCATE("getApplication"), OBFUSCATE("()Landroid/app/Application;"));
	jobject context = env->CallObjectMethod(at, getApplication);
	return context;
}

static std::string Clipboard() {
	std::string result;
	JNIEnv *env;
	JavaVm->AttachCurrentThread(&env, NULL);
	auto looperClass = env->FindClass(OBFUSCATE("android/os/Looper"));
	auto prepareMethod = env->GetStaticMethodID(looperClass, OBFUSCATE("prepare"), OBFUSCATE("()V"));
	env->CallStaticVoidMethod(looperClass, prepareMethod);
	jclass activityThreadClass = env->FindClass(OBFUSCATE("android/app/ActivityThread"));
	jfieldID sCurrentActivityThreadField = env->GetStaticFieldID(activityThreadClass, OBFUSCATE("sCurrentActivityThread"), OBFUSCATE("Landroid/app/ActivityThread;"));
	jobject sCurrentActivityThread = env->GetStaticObjectField(activityThreadClass, sCurrentActivityThreadField);
	jfieldID mInitialApplicationField = env->GetFieldID(activityThreadClass, OBFUSCATE("mInitialApplication"), OBFUSCATE("Landroid/app/Application;"));
	jobject mInitialApplication = env->GetObjectField(sCurrentActivityThread, mInitialApplicationField);
	auto contextClass = env->FindClass(OBFUSCATE("android/content/Context"));
	auto getSystemServiceMethod = env->GetMethodID(contextClass, OBFUSCATE("getSystemService"), OBFUSCATE("(Ljava/lang/String;)Ljava/lang/Object;"));
	auto str = env->NewStringUTF(OBFUSCATE("clipboard"));
	auto clipboardManager = env->CallObjectMethod(mInitialApplication, getSystemServiceMethod, str);
	env->DeleteLocalRef(str);
	jclass ClipboardManagerClass = env->FindClass(OBFUSCATE("android/content/ClipboardManager"));
    auto getText = env->GetMethodID(ClipboardManagerClass, OBFUSCATE("getText"), OBFUSCATE("()Ljava/lang/CharSequence;"));
    jclass CharSequenceClass = env->FindClass(OBFUSCATE("java/lang/CharSequence"));
    auto toStringMethod = env->GetMethodID(CharSequenceClass, OBFUSCATE("toString"), OBFUSCATE("()Ljava/lang/String;"));
    auto text = env->CallObjectMethod(clipboardManager, getText);
    if (text) {
        str = (jstring) env->CallObjectMethod(text, toStringMethod);
        result = env->GetStringUTFChars(str, 0);
        env->DeleteLocalRef(str);
        env->DeleteLocalRef(text);
    }
    env->DeleteLocalRef(CharSequenceClass);
    env->DeleteLocalRef(ClipboardManagerClass);
    env->DeleteLocalRef(clipboardManager);
    env->DeleteLocalRef(contextClass);
    env->DeleteLocalRef(mInitialApplication);
    env->DeleteLocalRef(activityThreadClass); 	
    JavaVm->DetachCurrentThread();
    return result.c_str();
}

void loadLibrary(const char *libname){
	JNIEnv *env;
	JavaVm->AttachCurrentThread(&env, NULL);
	// Load the native library using System.loadLibrary
	jclass systemClass = env->FindClass("java/lang/System");
	jmethodID loadLibraryMethod = env->GetStaticMethodID(systemClass, "loadLibrary", "(Ljava/lang/String;)V");
	jstring libraryName = env->NewStringUTF(libname);
	env->CallStaticVoidMethod(systemClass, loadLibraryMethod, libraryName);
	JavaVm->DetachCurrentThread();
}
class SharedPreferences_Editor {
private:
	JNIEnv* env;
	jobject joSharedPreferences_Edit;
	jmethodID jmPutBoolean;
	jmethodID jmPutInt;
	jmethodID jmPutFloat;
	jmethodID jmPutString;
	jmethodID jmCommit;
public:
	SharedPreferences_Editor(JNIEnv* env,const jobject joSharedPreferences_Edit):env(env),joSharedPreferences_Edit(joSharedPreferences_Edit) {
		jclass jcSharedPreferences_Editor = env->GetObjectClass(joSharedPreferences_Edit);
		jmPutBoolean = env->GetMethodID(jcSharedPreferences_Editor, OBFUSCATE("putBoolean"), OBFUSCATE("(Ljava/lang/String;Z)Landroid/content/SharedPreferences$Editor;"));
		jmPutInt = env->GetMethodID(jcSharedPreferences_Editor, OBFUSCATE("putInt"), OBFUSCATE("(Ljava/lang/String;I)Landroid/content/SharedPreferences$Editor;"));
		jmPutFloat = env->GetMethodID(jcSharedPreferences_Editor, OBFUSCATE("putFloat"), OBFUSCATE("(Ljava/lang/String;F)Landroid/content/SharedPreferences$Editor;"));
		jmPutString = env->GetMethodID(jcSharedPreferences_Editor, OBFUSCATE("putString"), OBFUSCATE("(Ljava/lang/String;Ljava/lang/String;)Landroid/content/SharedPreferences$Editor;"));
		jmCommit = env->GetMethodID(jcSharedPreferences_Editor, OBFUSCATE("commit"), OBFUSCATE("()Z"));
	}
	const SharedPreferences_Editor& putBoolean(const char* key,const bool value)const {
		env->CallObjectMethod(joSharedPreferences_Edit,jmPutBoolean,env->NewStringUTF(key),(jboolean)value);
		return *this;
	}
	const SharedPreferences_Editor& putInt(const char* key,const int value)const {
		env->CallObjectMethod(joSharedPreferences_Edit,jmPutInt,env->NewStringUTF(key),(jint)value);
		return *this;
	}
	const SharedPreferences_Editor& putFloat(const char* key,const float value)const {
		env->CallObjectMethod(joSharedPreferences_Edit, jmPutFloat, env->NewStringUTF(key), (jfloat)value);
		return *this;
	}
	const SharedPreferences_Editor& putString(const char* key,const char* value)const {
		env->CallObjectMethod(joSharedPreferences_Edit, jmPutString, env->NewStringUTF(key), env->NewStringUTF(value));
		return *this;
	}
	bool commit()const {
		return (bool)env->CallBooleanMethod(joSharedPreferences_Edit,jmCommit);
	}
};

class SharedPreferences {
public:
	SharedPreferences(SharedPreferences const &) = delete;
	void operator = (SharedPreferences const &) = delete;
public:
	SharedPreferences(JNIEnv *env, jobject androidContext,const char* name,const bool keepReference=false) {
		this->env = env;
		jclass jcContext = env->FindClass(OBFUSCATE("android/content/Context"));
		jclass jcSharedPreferences = env->FindClass(OBFUSCATE("android/content/SharedPreferences"));
		jmGetBoolean = env->GetMethodID(jcSharedPreferences, OBFUSCATE("getBoolean"), OBFUSCATE("(Ljava/lang/String;Z)Z"));
		jmGetInt = env->GetMethodID(jcSharedPreferences, OBFUSCATE("getInt"), OBFUSCATE("(Ljava/lang/String;I)I"));
		jmGetFloat = env->GetMethodID(jcSharedPreferences, OBFUSCATE("getFloat"), OBFUSCATE("(Ljava/lang/String;F)F"));
		jmGetString = env->GetMethodID(jcSharedPreferences, OBFUSCATE("getString"), OBFUSCATE("(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;"));
		jmEdit = env->GetMethodID(jcSharedPreferences, OBFUSCATE("edit"), OBFUSCATE("()Landroid/content/SharedPreferences$Editor;"));
		jmethodID jmGetSharedPreferences=env->GetMethodID(jcContext, OBFUSCATE("getSharedPreferences"), OBFUSCATE("(Ljava/lang/String;I)Landroid/content/SharedPreferences;"));
		joSharedPreferences = env->CallObjectMethod(androidContext, jmGetSharedPreferences, env->NewStringUTF(name), MODE_PRIVATE);
		if (keepReference) {
			joSharedPreferences = env->NewWeakGlobalRef(joSharedPreferences);
		}
	}
	void replaceJNI(JNIEnv* newEnv) {
		env = newEnv;
	}
private:
	JNIEnv* env;
	jobject joSharedPreferences;
	jmethodID jmGetBoolean;
	jmethodID jmGetInt;
	jmethodID jmGetFloat;
	jmethodID jmGetString;
	jmethodID jmEdit;
public:
	bool getBoolean(const char* id,bool defaultValue = false) const {
		return (bool)(env->CallBooleanMethod(joSharedPreferences, jmGetBoolean, env->NewStringUTF(id), (jboolean)defaultValue));
	}
	int getInt(const char* id, int defaultValue = 0) const {
		return (int)(env->CallIntMethod(joSharedPreferences, jmGetInt, env->NewStringUTF(id), (jint)defaultValue));
	}
	float getFloat(const char* id,float defaultValue = 0.0f) const {
		return (float)(env->CallFloatMethod(joSharedPreferences, jmGetFloat, env->NewStringUTF(id), (jfloat)defaultValue));
	}
	std::string getString(const char* id, const char* defaultValue = "") const {
		auto value=(jstring)(env->CallObjectMethod(joSharedPreferences, jmGetString, env->NewStringUTF(id), env->NewStringUTF(defaultValue)));
		const char* valueP = env->GetStringUTFChars(value, nullptr);
		const std::string ret=std::string(valueP);
		env->ReleaseStringUTFChars(value, valueP);
		return ret;
	}
	SharedPreferences_Editor edit() const {
		jobject joSharedPreferences_Edit = env->CallObjectMethod(joSharedPreferences, jmEdit);
		SharedPreferences_Editor editor(env, joSharedPreferences_Edit);
		return editor;
	}
private:
	static constexpr const int  MODE_PRIVATE = 0;
};

void WriteToFile(std::string dir, std::string buf) {
    std::ofstream os(dir.c_str(), std::ios::trunc);
    os.write(buf.c_str(), buf.length());
    os.close();
}

bool CopyFile(const char *in, const char *out) {
    std::ifstream src(in, std::ios::binary);
    std::ofstream dest(out, std::ios::binary);
    dest << src.rdbuf();
    return src && dest;
}

bool CheckFile(const std::string &name) {
    std::ifstream f(name.c_str());
    return f.good();
}
