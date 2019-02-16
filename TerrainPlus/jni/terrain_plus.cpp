#include "terrain_plus.h"

#include "sidebar/SidebarManager.h"

#include "mcpe/item/ItemInstance.h"
#include "mcpe/item/Item.h"
#include "mcpe/client/MinecraftGame.h"
#include "mcpe/client/gui/screen/ScreenChooser.h"
#include "mcpe/level/biome/Biome.h"
#include "mcpe/entity/player/Player.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/level/chunk/LevelChunk.h"
#include "mcpe/util/ChunkBlockPos.h"
#include "mcpe/util/BlockPos.h"
#include "ui/BiomeEditScreen.h"

MinecraftGame* TerrainPlus::mMinecraftGame = 0;
SidebarManager TerrainPlus::mSidebarManager;
Biome* TerrainPlus::mTargetBiome = 0;
bool TerrainPlus::isEditing = false;

void (*TerrainPlus::onPlayerLoaded_)(MinecraftGame*,Player&) = 0;
void (*TerrainPlus::initMinecraftGame_)(MinecraftGame*) = 0;
void (*TerrainPlus::renderGamePlay_)(void*,ClientInstance&,UIControl&,int,RectangleArea&) = 0;
bool (*TerrainPlus::useItem_)(ItemInstance*,Player&) = 0;
bool (*TerrainPlus::useOn_)(ItemInstance*,Entity&, int, int, int, signed char, float, float, float);

void TerrainPlus::initMinecraftGame(MinecraftGame*self)
{
	initMinecraftGame_(mMinecraftGame = self);
	
	mSidebarManager = SidebarManager(*self);
}

void TerrainPlus::onPlayerLoaded(MinecraftGame*self,Player&p)
{
	onPlayerLoaded_(self,p);
	
	mTargetBiome = Biome::beaches;
	mSidebarManager.showNewSidebar("biomeeditor.ui.guide.title","biomeeditor.ui.guide.message",ItemInstance(*Item::mSlimeBall,1,0));
}

void TerrainPlus::renderGamePlay(void*self,ClientInstance&ci,UIControl&c,int i,RectangleArea&area)
{
	renderGamePlay_(self,ci,c,i,area);
	
	mSidebarManager.renderSidebars();
}

bool TerrainPlus::useItem(ItemInstance*self,Player&targetPlayer)
{
	bool result = useItem_(self,targetPlayer);
	
	if(!isEditing && self && self->getId() == ItemInstance(*Item::mSlimeBall).getId())
	{
		//Push menu screen
		if(mMinecraftGame->getScreen()->getScreenName()!="menu_screen")//menu_screen
		{
			ScreenChooser* chooser = mMinecraftGame->getScreenChooser();
			chooser->_pushScreen(std::make_shared<BiomeEditScreen>(*mMinecraftGame,*mMinecraftGame->getPrimaryClientInstance(),mTargetBiome),false);
		}
	}
	else if(isEditing && self && self->getId() == ItemInstance(*Item::mSlimeBall).getId())
	{
		isEditing = false;
		mSidebarManager.showNewSidebar("biomeeditor.ui.exited.title","biomeeditor.ui.exited.message",ItemInstance(*Item::mSlimeBall,1,0));
	}
	
	return result;
}
bool TerrainPlus::useOn(ItemInstance*instance,Entity&ent, int x, int y, int z, signed char side, float px, float py, float pz)
{
	bool result = useOn_(instance,ent,x,y,z,side,px,py,pz);
	
	if(isEditing && instance && instance->getId() == ItemInstance(*Item::mSlimeBall).getId())
	{
		BlockSource& region = ent.getRegion();
		LevelChunk* chunk = region.getChunkAt(x,y,z);
		chunk->setBiome(*mTargetBiome,ChunkBlockPos(BlockPos(x,y,z)));
	}
	
	return result;
}
