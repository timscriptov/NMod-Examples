#include "IronFurnaceScreenClassic.h"

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

IronFurnaceScreenClassic::IronFurnaceScreenClassic(MinecraftGame&game,ClientInstance&client,Player&p,BlockPos const&pos_):BaseContainerScreenClassic(game,client,p.getRegion(),p,"IronFurnace.gui.name")
{
	ironFurnace=(IronFurnaceBlockEntity*)source.getBlockEntity(pos_);
	pos=pos_;
}
std::string IronFurnaceScreenClassic::getScreenName()const
{
	return "ic_furnace_iron_screen";
}
std::string IronFurnaceScreenClassic::getScreenNameW()const
{
	return "ic_furnace_iron_screen";
}
void IronFurnaceScreenClassic::_buttonClicked(Button&b)
{
	BaseContainerScreenClassic::_buttonClicked(b);
}
void IronFurnaceScreenClassic::onInit()
{
	fireBackground_empty=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setFire(*mcGame,width/2-50,height/2-48,16,16,1.0,fireBackground_empty,true);
	tabElementList.emplace_back(fireBackground_empty);
	
	fireBackground_filled=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setFire(*mcGame,width/2-50,height/2-48,16,16,1.0,fireBackground_filled,false);
	tabElementList.emplace_back(fireBackground_filled);
	
	progress_empty=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setProcess(*mcGame,width/2-11,height/2-50,22,15,1.0,progress_empty,true);
	tabElementList.emplace_back(progress_empty);
	
	progress_filled=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setProcess(*mcGame,width/2-11,height/2-50,22,15,1.0,progress_filled,false);
	tabElementList.emplace_back(progress_filled);
	
	setUIProgress();
}
void IronFurnaceScreenClassic::onRender()
{
	setUIProgress();
}
void IronFurnaceScreenClassic::onItemPanelChanged(ItemPanel&p)
{
	ItemInstance item=p.getItem();
	if(!item.isNull())
		ironFurnace->setSlot(p.getID(),&item);
	else
		ironFurnace->setSlot(p.getID(),0);
}
void IronFurnaceScreenClassic::onRegisterPanels()
{
	registerNewItemPanel(width/2-53,height/2-72,20,20,ItemInstance());
	registerNewItemPanel(width/2-53,height/2-29,20,20,ItemInstance());
	registerNewItemPanel(width/2+22,height/2-53,20,20,ItemInstance());
}
void IronFurnaceScreenClassic::tick()
{
	BaseContainerScreenClassic::tick();
	
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
unsigned char IronFurnaceScreenClassic::getAddItemToItemPanelCount(ItemInstance const&i,ItemPanel&p)
{
	if(!ironFurnace->canPushInItem(p.getID(),i))
		return 0;
	return BaseContainerScreenClassic::getAddItemToItemPanelCount(i,p);
}
void IronFurnaceScreenClassic::setUIProgress()
{
	ProgressController::setFire(*mcGame,width/2-50,height/2-48,16,16,ironFurnace->getFireProgress(),fireBackground_filled,false);
	ProgressController::setProcess(*mcGame,width/2-11,height/2-50,22,15,ironFurnace->getBurnProgress(),progress_filled,false);
}
