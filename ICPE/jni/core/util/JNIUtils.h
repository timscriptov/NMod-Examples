#pragma once

#include <jni.h>
#include <string>

class JNIUtils
{
private:
	JavaVM* jvm;
public:
	JNIUtils(JavaVM&);
	JNIUtils()=delete;
	~JNIUtils()=default;
public:
	std::string getExternalStorageDirectory();
	std::string toString(jstring const&);
	jobject getMainActivityInstance();
};
