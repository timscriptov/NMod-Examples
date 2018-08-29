#include <jni.h>
//jni.h defines JNIEXPORT,jint,JavaVM,JNIEnv,jobject,etc.
#include "Substrate.h"
//Substrate.h defines MSHookFunction,which allows us to hook native methods.

#include "terrain_plus.h"

#include "mcpe/client/MinecraftGame.h"
#include "mcpe/client/renderer/HotBarDropRenderer.h"
#include "mcpe/item/ItemInstance.h"

//The following methods starts with "NMod" are hooks provided by NModAPI.
//They won't work if you don't define use_api:true in nmod_manifest.json!

extern "C"
{
	//Called when the native library is loaded successfully.
	//The game hasn't started yet,you can register hooks here.
	//libminecraftpe.so has already loaded.
	//com.mojang.minecraftpe.MainActivity hasn't created!DO NOT invoke non-static methods in com.mojang.minecraftpe.MainActivity!
	void NMod_OnLoad(JavaVM*vm,JNIEnv*env,const char* minecraft_version_name,const char*nmodapi_version_name,const char*minecraftpe_so_file_path)
	{
		//vm : JavaVM
		//env : JNIEnv.DO NOT cache it!
		//minecraft_version_name : const char*.The version name of minecraft.
		//nmodapi_version_name : const char*.The version name of nmodapi.
		//minecraftpe_so_file_path : const char*.The file path of libminecraftpe.so.Can be used for dlopen.
		
		//Open libminecraftpe.so
		void* imageMCPE = (void*)dlopen(minecraftpe_so_file_path,RTLD_LAZY);
		
		//Use dlsym to get symbol address here.
		
		//Hook methods
		
		MSHookFunction( (void*)&MinecraftGame::_initMinecraftGame,
		                (void*)&TerrainPlus::initMinecraftGame,
						(void**)&TerrainPlus::initMinecraftGame_);
		
		MSHookFunction( (void*)&HotBarDropRenderer::render,
		                (void*)&TerrainPlus::renderGamePlay,
						(void**)&TerrainPlus::renderGamePlay_);
		
		MSHookFunction( (void*)&MinecraftGame::onPlayerLoaded,
		                (void*)&TerrainPlus::onPlayerLoaded,
						(void**)&TerrainPlus::onPlayerLoaded_);
		
		MSHookFunction( (void*)&ItemInstance::use,
		                (void*)&TerrainPlus::useItem,
						(void**)&TerrainPlus::useItem_);
		
		MSHookFunction( (void*)&ItemInstance::useOn,
		                (void*)&TerrainPlus::useOn,
						(void**)&TerrainPlus::useOn_);
		
		//Close libminecraftpe.so
		dlclose(imageMCPE);
	}
	
	//Called when com.mojang.minecraftpe.MainActivity is first created.
	//Activity is created,you can invoke non-static methods here.
	void NMod_OnActivityCreate(JNIEnv*env,jobject thiz,jobject savedInstanceState)
	{
		//env : JNIEnv
		//thiz : jobject.<Lcom/mojang/minecraftpe/MainActivity;>
		//savedInstanceState : jobject.<Landroid/os/Bundle;>
	}
	
	//Called when com.mojang.minecraftpe.MainActivity is finished.
	void NMod_OnActivityFinish(JNIEnv*env,jobject thiz)
	{
		//env : JNIEnv
		//thiz : jobject.<Lcom/mojang/minecraftpe/MainActivity;>
	}
}



//Called when the native library is loaded.
//NMod_OnLoad will called later than it.
JNIEXPORT jint JNI_OnLoad(JavaVM*vm,void*)
{
	//Tell JavaVM the JNI version.
	return JNI_VERSION_1_6;
}
