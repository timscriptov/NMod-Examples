#include "ICPE.h"
#include "Substrate.h"
#include <jni.h>
#include <cmath>
#include <dlfcn.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <thread>
#include <fstream>
#include <memory>
#include <sstream>

#include "mcpe/item/Item.h"
#include "mcpe/item/enchant/Enchant.h"
#include "mcpe/block/Block.h"
#include "mcpe/block/BlockGraphics.h"
#include "mcpe/block/blocks/FlowerPotBlock.h"
#include "mcpe/blockentity/FurnaceBlockEntity.h"
#include "mcpe/client/ClientInstance.h"
#include "mcpe/client/MinecraftGame.h"
#include "mcpe/client/Minecraft.h"
#include "mcpe/client/MinecraftInputHandler.h"
#include "mcpe/client/MoveInput.h"
#include "mcpe/client/resources/Localization.h"
#include "mcpe/client/renderer/BlockTessellator.h"
#include "mcpe/client/gui/GuiData.h"
#include "mcpe/client/gui/screen/Screen.h"
#include "mcpe/client/gui/screen/ScreenChooser.h"
#include "mcpe/client/renderer/ScreenRenderer.h"
#include "mcpe/client/renderer/HotBarDropRenderer.h"
#include "mcpe/recipe/Recipes.h"
#include "mcpe/recipe/Recipe.h"
#include "mcpe/recipe/FurnaceRecipes.h"
#include "mcpe/gamemode/GameMode.h"
#include "mcpe/entity/player/LocalPlayer.h"
#include "mcpe/util/FullBlock.h"
#include "mcpe/util/ChunkPos.h"
#include "mcpe/level/Level.h"
#include "mcpe/level/Dimension.h"
#include "mcpe/level/chunk/LevelChunk.h"
#include "mcpe/level/biome/BiomeDecorator.h"

#include "items/Items.h"
#include "items/recipe/ICRecipes.h"
#include "blocks/Blocks.h"
#include "blocks/BlockTextures.h"
#include "blocks/cblockentity/CBlockEntityAPI.h"
#include "blocks/tessellator/CableTessellator.h"
#include "gen/FeatureGen.h"
#include "ui/UIScreenChooser.h"
#include "ui/renderer/RendererStack.h"
#include "util/ItemUtils.h"
#include "util/JNIUtils.h"
#include "util/sound/SoundManager.h"

void ICPE::launch(JavaVM*vm)
{
	//set jvm to it's value.
	jvm=vm;
	//set up MSHookFunctions
	setupMSHookFunctions();
	
	JNIUtils utils(*jvm);
	externalStorageDirectory=utils.getExternalStorageDirectory();
	CBlockEntityAPI::setup();
}
void ICPE::setupMSHookFunctions()
{
	MSHookFunction((void*)((void(BlockTessellator::*)(Block const&,BlockPos const&,unsigned char,bool))&BlockTessellator::tessellateInWorld),(void*)&tessellateInWorld,(void**)&tessellateInWorld_);
	MSHookFunction((void*)&Recipe::isAnyAuxValue,(void*)&isAnyAuxValue,(void**)&isAnyAuxValue_);
	MSHookFunction((void*)&FlowerPotBlock::isSupportedBlock,(void*)&isSupportedFlower,(void**)&isSupportedFlower_);
	MSHookFunction((void*)&Item::teardownItems,(void*)&teardownItems,(void**)&teardownItems_);
	MSHookFunction((void*)&Level::tick,(void*)&tickLevel,(void**)&tickLevel_);
	MSHookFunction((void*)&BiomeDecorator::decorate,(void*)&decorateChunk,(void**)&decorateChunk_);
	MSHookFunction((void*)&Recipes::init,(void*)&initRecipes,(void**)&initRecipes_);
	MSHookFunction((void*)&MinecraftGame::_initMinecraftGame,(void*)&initGame,(void**)&initGame_);
	MSHookFunction((void*)&Item::initCreativeItems,(void*)&initCreativeItems,(void**)&initCreativeItems_);
	MSHookFunction((void*)&Item::initClientData,(void*)&initItems,(void**)&initItems_);
	MSHookFunction((void*)&BlockGraphics::initBlocks,(void*)&initBlockGraphics,(void**)&initBlockGraphics_);
	MSHookFunction((void*)&BlockGraphics::teardownBlocks,(void*)&teardownBlocks,(void**)&teardownBlocks_);
	MSHookFunction((void*)&HotBarDropRenderer::render,(void*)&renderHotBar,(void**)&renderHotBar_);
	MSHookFunction((void*)&Block::initBlocks,(void*)&initBlocks,(void**)&initBlocks_);
}

void (*ICPE::decorateChunk_)(BiomeDecorator*,BlockSource*, Random&, Biome*, BlockPos const&, bool, float)=0;
void (*ICPE::initRecipes_)(Recipes*self)=0;
bool (*ICPE::tessellateInWorld_)(BlockTessellator*,Block const&,BlockPos const&,uchar,bool)=0;
void (*ICPE::initGame_)(MinecraftGame*)=0;
void (*ICPE::initCreativeItems_)()=0;
void (*ICPE::initItems_)()=0;
void (*ICPE::teardownItems_)()=0;
void (*ICPE::initItemsServer_)(ResourcePackManager&)=0;
void (*ICPE::initBlockGraphics_)(ResourcePackManager&)=0;
void (*ICPE::initBlocks_)()=0;
void (*ICPE::teardownBlocks_)()=0;
bool (*ICPE::isSupportedFlower_)(FlowerPotBlock const*const,Block const*,int)=0;
void (*ICPE::tickLevel_)(Level*)=0;
bool (*ICPE::isAnyAuxValue_)(int)=0;
void (*ICPE::renderHotBar_)(void*,ClientInstance&,UIControl&,int,RectangleArea&)=0;

MinecraftGame* ICPE::pMinecraftGame=0;
Level* ICPE::pLevel=0;
UIScreenChooser ICPE::mUIScreenChooser;
Random ICPE::mRandom;
const int ICPE::localKeyCode=3497615802;
JavaVM* ICPE::jvm=0;
std::string ICPE::externalStorageDirectory;
SoundManager ICPE::soundManager(*jvm);
RendererStack ICPE::mRendererStack;

bool ICPE::isSupportedFlower(FlowerPotBlock const*const self,Block const*block,int aux)
{
	//make rubber sapling can be plant into flower pot.
	return block==Block::mBlocks[IC::Blocks::ID::mRubberSapling]||isSupportedFlower_(self,block,aux);
}
void ICPE::decorateChunk(BiomeDecorator*decorator,BlockSource*s, Random&r, Biome*biome, BlockPos const&pos, bool b, float f)
{
	//generate ores&rubber trees.
	decorateChunk_(decorator,s,r,biome,pos,b,f);
	if(s)
		IC::FeatureGen::decorateChunk(decorator,*s,r,biome,pos);
}
void ICPE::initRecipes(Recipes*self)
{
	initRecipes_(self);
	//ICRecipes recipes(*self,*FurnaceRecipes::getInstance());
	//recipes.addRecipes();
}
bool ICPE::tessellateInWorld(BlockTessellator*tessellator,Block const&block,BlockPos const&pos,uchar aux,bool wtf)
{
	if(&block==Block::mBlocks[IC::Blocks::ID::mCable])
		return ((CableTessellator*)tessellator)->tessellate(block,pos,aux,wtf);
	return tessellateInWorld_(tessellator,block,pos,aux,wtf);
}
void ICPE::initGame(MinecraftGame*self)
{
	initGame_(self);
	pMinecraftGame=self;
	mUIScreenChooser=UIScreenChooser(*self);
	mRandom=Random((unsigned long int)time(0));
	soundManager=SoundManager(*jvm);
}
void ICPE::initCreativeItems()
{
	initCreativeItems_();
	IC::Items::addICCreativeItems();
}
void ICPE::initItems()
{
	initItems_();
	IC::Items::initICAllItems();
}
void ICPE::teardownItems()
{
	teardownItems_();
	IC::Items::teardownICItems();
}
void ICPE::initItemsServer(ResourcePackManager&m)
{
	initItemsServer_(m);
	IC::Items::initICAllItems();
}
void ICPE::initBlockGraphics(ResourcePackManager&m)
{
	initBlockGraphics_(m);
	BlockTextures::initBlockGraphics();
}
void ICPE::teardownBlocks()
{
	teardownBlocks_();
	BlockTextures::teardownBlockGraphics();
}
void ICPE::initBlocks()
{
	initBlocks_();
	IC::Blocks::initICBlocks();
}
void ICPE::tickLevel(Level*self)
{
	tickLevel_(self);
	pLevel=self;
}
bool ICPE::isAnyAuxValue(int id)
{
	if(id<=255&&IC::Blocks::mICBlocks[id])
		if(!((IC::Blocks*)Block::mBlocks[id])->isAnyAuxValueInRecipe())
			return false;
	return isAnyAuxValue_(id);
}
void ICPE::renderHotBar(void*v,ClientInstance&c,UIControl&s,int i,RectangleArea&r)
{
	renderHotBar_(v,c,s,i,r);
	
	mRendererStack.render();
}
