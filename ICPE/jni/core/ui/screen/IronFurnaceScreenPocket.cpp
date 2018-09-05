#include "IronFurnaceScreenPocket.h"

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

#include "blocks/blockentity/IronFurnaceBlockEntity.h"
#include "ui/ProgressController.h"

IronFurnaceScreenPocket::IronFurnaceScreenPocket(MinecraftGame&game,ClientInstance&client,Player&p,BlockPos const&pos_):BaseContainerScreenPocket(game,client,p.getRegion(),p,"IronFurnace.gui.name")
{
	ironFurnace=(IronFurnaceBlockEntity*)source.getBlockEntity(pos_);
	pos=pos_;
}
std::string IronFurnaceScreenPocket::getScreenName()const
{
	return "ic_furnace_iron_screen";
}
std::string IronFurnaceScreenPocket::getScreenNameW()const
{
	return "ic_furnace_iron_screen";
}
void IronFurnaceScreenPocket::_buttonClicked(Button&b)
{
	BaseContainerScreenPocket::_buttonClicked(b);
}
void IronFurnaceScreenPocket::onInit()
{
	fireBackground_empty=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setFire(*mcGame,width/2+7,height/2-10,20,20,1.0,fireBackground_empty,true);
	tabElementList.emplace_back(fireBackground_empty);
	
	fireBackground_filled=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setFire(*mcGame,width/2+7,height/2-10,20,20,1.0,fireBackground_filled,false);
	tabElementList.emplace_back(fireBackground_filled);
	
	progress_empty=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setProcess(*mcGame,35+width/2+((width/2-120)/2),height/2-10,36,20,1.0,progress_empty,true);
	tabElementList.emplace_back(progress_empty);
	
	progress_filled=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setProcess(*mcGame,35+width/2+((width/2-120)/2),height/2-10,36,20,1.0,progress_filled,false);
	tabElementList.emplace_back(progress_filled);
	
	setUIProgress();
}
void IronFurnaceScreenPocket::onRender()
{
	setUIProgress();
}
void IronFurnaceScreenPocket::onItemPanelChanged(ItemPanel&p)
{
	ItemInstance item=p.getItem();
	if(!item.isNull())
		ironFurnace->setSlot(p.getID(),&item);
	else
		ironFurnace->setSlot(p.getID(),0);
}
void IronFurnaceScreenPocket::onRegisterPanels()
{
	registerNewItemPanel(width/2,height/2-60,30,30,ItemInstance());
	registerNewItemPanel(width/2,height/2+25,30,30,ItemInstance());
	registerNewItemPanel(width-50,height/2-17,30,30,ItemInstance());
}
void IronFurnaceScreenPocket::tick()
{
	BaseContainerScreenPocket::tick();
	
	if(source.getBlockEntity(pos)!=ironFurnace)
	{
		mcGame->getScreenChooser()->schedulePopScreen(1);
		return;
	}
	for(int i=0;i<3;++i)
	{
		if(ironFurnace->getSlot(i))
			itemPanels[i]->item=*ironFurnace->getSlot(i);
	}
}
unsigned char IronFurnaceScreenPocket::getAddItemToItemPanelCount(ItemInstance const&i,ItemPanel&p)
{
	if(!ironFurnace->canPushInItem(p.getID(),i))
		return 0;
	return BaseContainerScreenPocket::getAddItemToItemPanelCount(i,p);
}
void IronFurnaceScreenPocket::setUIProgress()
{
	ProgressController::setProcess(*mcGame,35+width/2+((width/2-120)/2),height/2-10,36,20,ironFurnace->getBurnProgress(),progress_filled,false);
	ProgressController::setFire(*mcGame,width/2+7,height/2-10,20,20,ironFurnace->getFireProgress(),fireBackground_filled,false);
}
