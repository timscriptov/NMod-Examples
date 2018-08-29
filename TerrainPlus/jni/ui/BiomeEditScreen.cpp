#include "BiomeEditScreen.h"

#include "elements/TabButton.h"

#include "mcpe/client/gui/Font.h"
#include "mcpe/client/gui/screen/ScreenChooser.h"
#include "mcpe/client/resources/I18n.h"
#include "mcpe/client/MinecraftGame.h"
#include "mcpe/client/renderer/ScreenRenderer.h"
#include "mcpe/level/biome/Biome.h"
#include "mcpe/item/Item.h"
#include "mcpe/item/ItemInstance.h"

#include "sidebar/SidebarManager.h"
#include "terrain_plus.h"

BiomeEditScreen::BiomeEditScreen(MinecraftGame&game,ClientInstance&instance,Biome*&biome)
:MenuScreen(game,instance,"biomeeditor.menu.main.title",300,150)
,mTargetBiome(biome)
{
	
}
void BiomeEditScreen::init()
{
	MenuScreen::init();
	
	initBiomeData();
	
	mSelectButton = std::make_shared<TabButton>(1000,"biomeeditor.ui.start");
	buttonList.push_back(mSelectButton);
	
	mPrevButton = std::make_shared<TabButton>(1001,"<");
	buttonList.push_back(mPrevButton);
	
	mNextButton = std::make_shared<TabButton>(1002,">");
	buttonList.push_back(mNextButton);
}
void BiomeEditScreen::setupPositions()
{
	MenuScreen::setupPositions();
	
	mSelectButton -> xPosition = getMenuXPosition() + 80;
	mSelectButton -> yPosition = getMenuYPosition() + getMenuHeight() - 35;
	mSelectButton -> width = getMenuWidth() - 160;
	mSelectButton -> height = 25;
	
	mPrevButton -> xPosition = getMenuXPosition() + 30;
	mPrevButton -> yPosition = getMenuYPosition() + getMenuHeight() - 35;
	mPrevButton -> width = 25;
	mPrevButton -> height = 25;
	
	mNextButton -> xPosition = getMenuXPosition() + getMenuWidth() - 55;
	mNextButton -> yPosition = getMenuYPosition() + getMenuHeight() - 35;
	mNextButton -> width = 25;
	mNextButton -> height = 25;
}
void BiomeEditScreen::render(int xPos,int yPos,float f)
{
	MenuScreen::render(xPos,yPos,f);
	
	ScreenRenderer::singletonPtr->drawCenteredString(mcGame->getFont(),I18n::get("biomeeditor.type." + biomeToString()),width / 2,height / 2 - 4,Color::GREY);
}
void BiomeEditScreen::_buttonClicked(Button&button)
{
	MenuScreen::_buttonClicked(button);
	
	if(&button == mSelectButton.get())
	{
		mcGame->schedulePopScreen(1);
		TerrainPlus::mSidebarManager.showNewSidebar("biomeeditor.ui.selected.title","biomeeditor.ui.selected.message",ItemInstance(*Item::mFeather));
		TerrainPlus::mSidebarManager.showNewSidebar("biomeeditor.ui.started.title","biomeeditor.ui.started.message",ItemInstance(*Item::mSlimeBall));
		TerrainPlus::isEditing = true;
	}
	else if(&button == mPrevButton.get())
	{
		prev();
	}
	else if(&button == mNextButton.get())
	{
		next();
	}
}
void BiomeEditScreen::initBiomeData()
{
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::beaches,"beaches"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::birchForest,"birchForest"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::birchForestHills,"birchForestHills"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::birchForestHillsMutated,"birchForestHillsMutated"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::birchForestMutated,"birchForestMutated"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::coldBeach,"coldBeach"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::deepOcean,"deepOcean"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::desert,"desert"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::desertHills,"desertHills"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::desertMutated,"desertMutated"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::extremeHills,"extremeHills"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::extremeHillsMutated,"extremeHillsMutated"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::extremeHillsWithTrees,"extremeHillsWithTrees"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::extremeHillsWithTreesMutated,"extremeHillsWithTreesMutated"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::forest,"forest"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::forestHills,"forestHills"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::forestMutated,"forestMutated"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::frozenOcean,"frozenOcean"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::frozenRiver,"frozenRiver"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::hell,"hell"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::iceFlats,"iceFlats"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::iceFlatsMutated,"iceFlatsMutated"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::iceMountains,"iceMountains"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::jungle,"jungle"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::jungleEdge,"jungleEdge"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::jungleEdgeMutated,"jungleEdgeMutated"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::jungleHills,"jungleHills"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::jungleMutated,"jungleMutated"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::mesa,"mesa"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::mesaClearRock,"mesaClearRock"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::mesaClearRockMutated,"mesaClearRockMutated"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::mesaMutated,"mesaMutated"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::mesaRock,"mesaRock"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::mesaRockMutated,"mesaRockMutated"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::mushroomIsland,"mushroomIsland"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::mushroomIslandShore,"mushroomIslandShore"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::ocean,"ocean"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::plains,"plains"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::plainsMutated,"plainsMutated"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::redwoodTaiga,"redwoodTaiga"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::redwoodTaigaHills,"redwoodTaigaHills"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::redwoodTaigaHillsMutated,"redwoodTaigaHillsMutated"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::redwoodTaigaMutated,"redwoodTaigaMutated"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::river,"river"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::roofedForest,"roofedForest"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::roofedForestMutated,"roofedForestMutated"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::savanna,"savanna"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::savannaMutated,"savannaMutated"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::savannaRock,"savannaRock"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::savannaRockMutated,"savannaRockMutated"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::sky,"sky"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::smallerExtremeHills,"smallerExtremeHills"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::stoneBeach,"stoneBeach"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::swampland,"swampland"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::swamplandMutated,"swamplandMutated"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::taiga,"taiga"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::taigaCold,"taigaCold"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::taigaColdHills,"taigaColdHills"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::taigaColdMutated,"taigaColdMutated"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::taigaHills,"taigaHills"));
	mBiomeData.insert(std::pair<Biome*,std::string>(Biome::taigaMutated,"taigaMutated"));
}
std::string BiomeEditScreen::biomeToString()const
{
	std::map<Biome*,std::string>::const_iterator iter = mBiomeData.find(mTargetBiome);
	if(iter != mBiomeData.end() && (*iter).first == mTargetBiome)
		return (*iter).second;
	return "null";
}
void BiomeEditScreen::prev()
{
	std::map<Biome*,std::string>::iterator iter = mBiomeData.find(mTargetBiome);
	if(iter == mBiomeData.end())
		return;
	if(iter == mBiomeData.begin())
	{
		mTargetBiome = (*(--mBiomeData.end())).first;
		return;
	}
	mTargetBiome = (*(--iter)).first;
}
void BiomeEditScreen::next()
{
	std::map<Biome*,std::string>::iterator iter = mBiomeData.find(mTargetBiome);
	if(iter == mBiomeData.end())
		return;
	if(iter == (--mBiomeData.end()) )
	{
		mTargetBiome = (*(mBiomeData.begin())).first;
		return;
	}
	mTargetBiome = (*(++iter)).first;
}
