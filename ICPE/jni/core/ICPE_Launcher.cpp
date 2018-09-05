#include <jni.h>
#include <string>

#include "ICPE.h"

extern "C"
{
	void NMod_onLoad(JavaVM*jvm,JNIEnv* env,std::string const& mcVersionName,std::string const& moddedpeVersionName)
	{
		ICPE::launch(jvm);
	}

	void NMod_onActivityCreate(JNIEnv*env,jobject thiz,jobject savedInstanceState)
	{
		
	}

	void NMod_onActivityFinish(JNIEnv*env,jobject thiz)
	{
		
	}
	
	JNIEXPORT jint JNI_OnLoad(JavaVM*,void*)
	{
		return JNI_VERSION_1_6;
	}
}
