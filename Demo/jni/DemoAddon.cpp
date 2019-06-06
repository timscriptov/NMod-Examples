#include <jni.h>
#include <string>
#include "Substrate.h"

struct GuiData
{
	void displayClientMessage(std::string const&);
};
struct Player;
struct MinecraftClient
{
	void onPlayerLoaded(Player&);
	GuiData* getGuiData();
};

void (*onPlayerLoaded_)(MinecraftClient*,Player&);
void onPlayerLoaded(MinecraftClient*mc,Player&p)
{
	onPlayerLoaded_(mc,p);
	mc->getGuiData()->displayClientMessage("hello world!");
}

JNIEXPORT jint JNI_OnLoad(JavaVM*,void*)
{
	MSHookFunction((void*)&MinecraftClient::onPlayerLoaded,(void*)&onPlayerLoaded,(void**)&onPlayerLoaded_);
	return JNI_VERSION_1_6;
}
