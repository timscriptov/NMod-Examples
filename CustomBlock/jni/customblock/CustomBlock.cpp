#include <jni.h>
#include "Substrate.h"

#include "mcpe/item/BlockItem.h"
#include "mcpe/item/AuxDataBlockItem.h"
#include "mcpe/block/Block.h"
#include "mcpe/block/BlockGraphics.h"

#include "blocks/ExtendsBlock.h"
#include "blocks/CustomAuxDataBlock.h"

void registerCustomBlocks()
{
	//define block directly
	Block& custom_block = registerBlock<Block>("custom_block",225,Material::getMaterial(MaterialType::DEVICE));
	custom_block.setCategory(CreativeItemCategory::BLOCKS);
	custom_block.setVisualShape(AABB(0.4375,0,0.4375,0.5625,1,0.5625));
	custom_block.setLightEmission(1.0);
	custom_block.setExplodeable(1E2);
	custom_block.setDestroyTime(-1);
	custom_block.setSolid(false);
	//define block by extending
	ExtendsBlock& custom_extends_block = registerBlock<ExtendsBlock>("custom_extends_block",224);
	
	//define block with aux data
	CustomAuxDataBlock& custom_auxdata_block = registerBlock<CustomAuxDataBlock>("aux_data_custom_block",246);
}

void registerCustomBlockItems()
{
	registerCustomBlocks();
	
	//define block directly
	
	registerItem<BlockItem>("custom_block",225-256).setCategory(CreativeItemCategory::BLOCKS);
	
	//define block by extending
	registerItem<BlockItem>("custom_extends_block",224-256).setCategory(CreativeItemCategory::BLOCKS);
	//define block with aux data
	registerItem<AuxDataBlockItem>("aux_data_custom_block",246-256,Block::mBlocks[246]).setCategory(CreativeItemCategory::BLOCKS);
}

static void (*registerItems_)();
static void registerItems()
{
	registerItems_();
	
	registerCustomBlockItems();
}

static void (*addBlockItems_)();
static void addBlockItems()
{
	addBlockItems_();
	
	registerCustomBlockItems();
	/*
	Item::addCreativeItem(225,0);
	Item::addCreativeItem(224,0);
	Item::addCreativeItem(246,0);
	Item::addCreativeItem(246,1);
	*/
}

static void (*initBlockGraphics_)();
static void initBlockGraphics()
{
	initBlockGraphics_();
	
	//define block directly
	BlockGraphics::mBlocks[225]=new BlockGraphics("portal");
	BlockGraphics::mBlocks[225]->setTextureItem("beacon");
	
	//define block by extending
	BlockGraphics::mBlocks[224]=new BlockGraphics("portal");
	BlockGraphics::mBlocks[224]->setTextureItem("portal");
	
	//define block with aux data
	BlockGraphics::mBlocks[246]=new BlockGraphics("dirt");
	BlockGraphics::mBlocks[246]->setTextureItem("planks");
}

static void (*initBlocks_)();
static void initBlocks()
{
	initBlocks_();
	
	registerCustomBlocks();
}

JNIEXPORT jint JNI_OnLoad(JavaVM*,void*)
{
	MSHookFunction((void*)&BlockGraphics::initBlocks,(void*)&initBlockGraphics,(void**)&initBlockGraphics_);
	MSHookFunction((void*)&Block::initBlocks,(void*)&initBlocks,(void**)&initBlocks_);
	MSHookFunction((void*)&Item::addBlockItems,(void*)&addBlockItems,(void**)&addBlockItems_);
	MSHookFunction((void*)&Item::registerItems,(void*)&registerItems,(void**)&registerItems_);
	return JNI_VERSION_1_6;
}
