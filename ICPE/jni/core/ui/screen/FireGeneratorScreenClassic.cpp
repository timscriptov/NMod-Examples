#include "FireGeneratorScreenClassic.h"

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

FireGeneratorScreenClassic::FireGeneratorScreenClassic(MinecraftGame&game,ClientInstance&client,Player&p,BlockPos const&pos_):BaseContainerScreenClassic(game,client,p.getRegion(),p,"te.generator")
{
	generator=(FireGeneratorBlockEntity*)source.getBlockEntity(pos_);
	pos=pos_;
}
std::string FireGeneratorScreenClassic::getScreenName()const
{
	return "ic_generator_screen";
}
std::string FireGeneratorScreenClassic::getScreenNameW()const
{
	return "ic_generator_screen";
}
void FireGeneratorScreenClassic::_buttonClicked(Button&b)
{
	BaseContainerScreenClassic::_buttonClicked(b);
}
void FireGeneratorScreenClassic::onInit()
{
	fireBackground_empty=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setFire(*mcGame,width/2-50,height/2-48,16,16,1.0,fireBackground_empty,true);
	tabElementList.emplace_back(fireBackground_empty);
	
	fireBackground_filled=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setFire(*mcGame,width/2-50,height/2-48,16,16,1.0,fireBackground_filled,false);
	tabElementList.emplace_back(fireBackground_filled);
	
	progress_empty=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setEnergyLarge(*mcGame,width/2-11,height/2-51,32,17,1.0,progress_empty,true);
	tabElementList.emplace_back(progress_empty);
	
	progress_filled=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setEnergyLarge(*mcGame,width/2-11,height/2-51,32,17,1.0,progress_filled,false);
	tabElementList.emplace_back(progress_filled);
	
	setUIProgress();
}
void FireGeneratorScreenClassic::onRender()
{
	setUIProgress();
}
void FireGeneratorScreenClassic::onItemPanelChanged(ItemPanel&p)
{
	ItemInstance item=p.getItem();
	if(!item.isNull())
		generator->setSlot(p.getID(),&item);
	else
		generator->setSlot(p.getID(),0);
}
void FireGeneratorScreenClassic::onRegisterPanels()
{
	registerNewItemPanel(width/2-53,height/2-72,20,20,ItemInstance());
	registerNewItemPanel(width/2-53,height/2-29,20,20,ItemInstance());
}
void FireGeneratorScreenClassic::tick()
{
	BaseContainerScreenClassic::tick();
	
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
unsigned char FireGeneratorScreenClassic::getAddItemToItemPanelCount(ItemInstance const&i,ItemPanel&p)
{
	if(!generator->canPushInItem(p.getID(),i))
		return 0;
	return BaseContainerScreenClassic::getAddItemToItemPanelCount(i,p);
}
void FireGeneratorScreenClassic::setUIProgress()
{
	ProgressController::setEnergyLarge(*mcGame,width/2-11,height/2-51,32,17,generator->getEnergyProgress(),progress_filled,false);
	ProgressController::setFire(*mcGame,width/2-50,height/2-48,16,16,generator->getFireProgress(),fireBackground_filled,false);
}
