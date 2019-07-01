#include <jni.h>
#include <dlfcn.h>
#include "Substrate.h"
#include "mcpe.h"

static std::string (*_I18n_get)(std::string const&);
static std::string I18n_get(std::string const& str) {
    //return _I18n_get(str);
	// We don't want to call the original function here
    return " ";
}

JNIEXPORT jint JNI_OnLoad(JavaVM*vm,void*)
{
	void* imageMCPE = dlopen("libminecraftpe.so", RTLD_LAZY);
	MSHookFunction(
		(void*)dlsym(handler, "_ZN4I18n3getERKSs"), 	// I18n::get(std::string const&)
		(void*)&I18n_get, 
		(void**)&_I18n_get
	);
	dlclose(imageMCPE);
	return JNI_VERSION_1_6;
}
