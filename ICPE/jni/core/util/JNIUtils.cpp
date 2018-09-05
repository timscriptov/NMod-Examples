#include "JNIUtils.h"

JNIUtils::JNIUtils(JavaVM&vm)
{
	jvm=&vm;
}
std::string JNIUtils::getExternalStorageDirectory()
{
	JNIEnv* env=NULL;
	jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
	jclass jEnvironnent = env->FindClass("android/os/Environment");
	jmethodID getExternalMid = env->GetStaticMethodID(jEnvironnent, "getExternalStorageDirectory","()Ljava/io/File;");
	jobject filePath = (jobject) env->CallStaticObjectMethod(jEnvironnent,getExternalMid);
	jclass jFile = env->FindClass("java/io/File");
	jmethodID getPathMid = env->GetMethodID(jFile, "getPath","()Ljava/lang/String;");
	jstring finalPath= (jstring)env->CallObjectMethod(filePath,getPathMid);
	return toString(finalPath);
}
jobject JNIUtils::getMainActivityInstance()
{
	JNIEnv* env=NULL;
	jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
	jclass jMainActivity = env->FindClass("com/mojang/minecraftpe/MainActivity");
	jfieldID mInstanceFID = env->GetStaticFieldID(jMainActivity,"currentMainActivity","Ljava/lang/ref/WeakReference;");
	jobject mReference = env->GetStaticObjectField(jMainActivity,mInstanceFID);
	jclass jRef = env->FindClass("java/lang/ref/WeakReference");
	jmethodID getmid = env->GetMethodID(jRef, "get","()Ljava/lang/Object;");
	jobject mActivityInstance = env->CallObjectMethod(mReference,getmid);
	return mActivityInstance;
}
std::string JNIUtils::toString(jstring const&jstr)
{
	JNIEnv* env=NULL;
	jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
	char const* rtn = NULL;
	rtn = env->GetStringUTFChars(jstr,0);
	std::string stemp(rtn);
	env->ReleaseStringUTFChars(jstr,0);
	return stemp;
}
