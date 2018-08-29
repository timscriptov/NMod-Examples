#include <jni.h>
#include <fstream>
#include "Substrate.h"

#include "mcpe/item/Item.h"
#include "mcpe/util/Util.h"

#include "items/ExtendsItem.h"
#include "items/AuxDataCustomItem.h"

void registerCustomItems()
{
	//define item directly
	Item& customItem = registerItem<Item>("custom_item",470 - 0x100);
	customItem.setIsGlint(true);
	customItem.setCategory(CreativeItemCategory::ITEMS);
	
	//define item by extending
	Item& custom_extends_Item = registerItem<ExtendsItem>("custom_extends_item",471 - 0x100);
	
	//define item with aux data
	Item& custom_auxdata_Item = registerItem<AuxDataCustomItem>("aux_data_custom_item",472 - 0x100);
}

void (*registerItems_)();
void registerItems()
{
	registerItems_();
	registerCustomItems();
}

void (*initCreativeItems_)();
void initCreativeItems()
{
	initCreativeItems_();
	
	registerCustomItems();
	
	Item::addCreativeItem(470,0);
	Item::addCreativeItem(471,0);
	Item::addCreativeItem(472,0);
	Item::addCreativeItem(472,1);
}

void (*initClientData_)();
void initClientData()
{
	initClientData_();
	
	registerCustomItems();
	
	Item::mItems[470]->setIcon("ender_pearl",0);
	Item::mItems[471]->setIcon("apple",0);
}


JNIEXPORT jint JNI_OnLoad(JavaVM*,void*)
{
	MSHookFunction((void*)&Item::initClientData,(void*)&initClientData,(void**)&initClientData_);
	MSHookFunction((void*)&Item::initCreativeItems,(void*)&initCreativeItems,(void**)&initCreativeItems_);
	MSHookFunction((void*)&Item::registerItems,(void*)&registerItems,(void**)&registerItems_);
	return JNI_VERSION_1_6;
}
