#pragma once

#include <jni.h>

class JavaUtil
{
public:
	static void getXblInviteJson();
	static void setXblInviteJson(std::string);
	static JavaVM* getVM();
	static jobject getActivityObject();
	static void setActivityObject(jobject);
	static void setVM(JavaVM*);
};
