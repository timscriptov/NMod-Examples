#include "FireGeneratorScreenPocket.h"

#include <math.h>

#include "mcpe/entity/player/Player.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/util/BlockPos.h"
#include "mcpe/client/resources/I18n.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/client/MinecraftGame.h"
#include "mcpe/client/gui/screen/ScreenChooser.h"
#include "mcpe/client/gui/GuiData.h"
#include "mcpe/client/gui/GuiElement.h"
#include "mcpe/item/ItemInstance.h"
#include "mcpe/client/gui/IntRectangle.h"

#include "blocks/blockentity/FireGeneratorBlockEntity.h"
#include "ui/ProgressController.h"

FireGeneratorScreenPocket::FireGeneratorScreenPocket(MinecraftGame&game,ClientInstance&client,Player&p,BlockPos const&pos_):BaseContainerScreenPocket(game,client,p.getRegion(),p,"te.generator")
{
	generator=(FireGeneratorBlockEntity*)source.getBlockEntity(pos_);
	pos=pos_;
}
std::string FireGeneratorScreenPocket::getScreenName()const
{
	return "ic_generator_screen";
}
std::string FireGeneratorScreenPocket::getScreenNameW()const
{
	return "ic_generator_screen";
}
void FireGeneratorScreenPocket::_buttonClicked(Button&b)
{
	BaseContainerScreenPocket::_buttonClicked(b);
}
void FireGeneratorScreenPocket::onInit()
{
	fireBackground_empty=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setFire(*mcGame,width/2+7,height/2-10,20,20,1.0,fireBackground_empty,true);
	tabElementList.emplace_back(fireBackground_empty);
	
	fireBackground_filled=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setFire(*mcGame,width/2+7,height/2-10,20,20,1.0,fireBackground_filled,false);
	tabElementList.emplace_back(fireBackground_filled);
	
	progress_empty=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setEnergyLarge(*mcGame,35+width/2+((width/2-120)/2),height/2-10,36,20,1.0,progress_empty,true);
	tabElementList.emplace_back(progress_empty);
	
	progress_filled=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setEnergyLarge(*mcGame,35+width/2+((width/2-120)/2),height/2-10,36,20,1.0,progress_filled,false);
	tabElementList.emplace_back(progress_filled);
	
	setUIProgress();
}
void FireGeneratorScreenPocket::onRender()
{
	setUIProgress();
}
void FireGeneratorScreenPocket::onItemPanelChanged(ItemPanel&p)
{
	ItemInstance item=p.getItem();
	if(!item.isNull())
		generator->setSlot(p.getID(),&item);
	else
		generator->setSlot(p.getID(),0);
}
void FireGeneratorScreenPocket::onRegisterPanels()
{
	registerNewItemPanel(width/2,height/2-60,30,30,ItemInstance());
	registerNewItemPanel(width/2,height/2+25,30,30,ItemInstance());
}
void FireGeneratorScreenPocket::tick()
{
	BaseContainerScreenPocket::tick();
	
	if(source.getBlockEntity(pos)!=generator)
	{
		mcGame->getScreenChooser()->schedulePopScreen(1);
		return;
	}
	for(int i=0;i<2;++i)
	{
		if(generator->getSlot(i))
			itemPanels[i]->item=*generator->getSlot(i);
	}
}
unsigned char FireGeneratorScreenPocket::getAddItemToItemPanelCount(ItemInstance const&i,ItemPanel&p)
{
	if(!generator->canPushInItem(p.getID(),i))
		return 0;
	return BaseContainerScreenPocket::getAddItemToItemPanelCount(i,p);
}
void FireGeneratorScreenPocket::setUIProgress()
{
	ProgressController::setEnergyLarge(*mcGame,35+width/2+((width/2-120)/2),height/2-10,36,20,generator->getEnergyProgress(),progress_filled,false);
	ProgressController::setFire(*mcGame,width/2+7,height/2-10,20,20,generator->getFireProgress(),fireBackground_filled,false);
}
