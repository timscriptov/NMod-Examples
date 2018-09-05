#include "ElectricFurnaceScreenClassic.h"

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

#include "blocks/blockentity/ElectricFurnaceBlockEntity.h"
#include "ui/ProgressController.h"

ElectricFurnaceScreenClassic::ElectricFurnaceScreenClassic(MinecraftGame&game,ClientInstance&client,Player&p,BlockPos const&pos_):BaseContainerScreenClassic(game,client,p.getRegion(),p,"ElecFurnace.gui.name")
{
	electricFurnace=(ElectricFurnaceBlockEntity*)source.getBlockEntity(pos_);
	pos=pos_;
}
std::string ElectricFurnaceScreenClassic::getScreenName()const
{
	return "ic_furnace_electric_screen";
}
std::string ElectricFurnaceScreenClassic::getScreenNameW()const
{
	return "ic_furnace_electric_screen";
}
void ElectricFurnaceScreenClassic::_buttonClicked(Button&b)
{
	BaseContainerScreenClassic::_buttonClicked(b);
}
void ElectricFurnaceScreenClassic::onInit()
{
	energyBackground_empty=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setEnergySmall(*mcGame,width/2-50,height/2-48,16,16,1.0,energyBackground_empty,true);
	tabElementList.emplace_back(energyBackground_empty);
	
	energyBackground_filled=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setEnergySmall(*mcGame,width/2-50,height/2-48,16,16,1.0,energyBackground_filled,false);
	tabElementList.emplace_back(energyBackground_filled);
	
	progress_empty=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setProcess(*mcGame,width/2-11,height/2-50,22,15,1.0,progress_empty,true);
	tabElementList.emplace_back(progress_empty);
	
	progress_filled=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setProcess(*mcGame,width/2-11,height/2-50,22,15,1.0,progress_filled,false);
	tabElementList.emplace_back(progress_filled);
	
	setUIProgress();
}
void ElectricFurnaceScreenClassic::onRender()
{
	setUIProgress();
}
void ElectricFurnaceScreenClassic::onItemPanelChanged(ItemPanel&p)
{
	ItemInstance item=p.getItem();
	if(!item.isNull())
		electricFurnace->setSlot(p.getID(),&item);
	else
		electricFurnace->setSlot(p.getID(),0);
}
void ElectricFurnaceScreenClassic::onRegisterPanels()
{
	registerNewItemPanel(width/2-53,height/2-72,20,20,ItemInstance());
	registerNewItemPanel(width/2-53,height/2-29,20,20,ItemInstance());
	registerNewItemPanel(width/2+22,height/2-53,20,20,ItemInstance());
}
void ElectricFurnaceScreenClassic::tick()
{
	BaseContainerScreenClassic::tick();
	
	if(source.getBlockEntity(pos)!=electricFurnace)
	{
		mcGame->getScreenChooser()->schedulePopScreen(1);
		return;
	}
	for(int i=0;i<3;++i)
	{
		if(electricFurnace->getSlot(i))
			itemPanels[i]->item=*electricFurnace->getSlot(i);
	}
}
unsigned char ElectricFurnaceScreenClassic::getAddItemToItemPanelCount(ItemInstance const&i,ItemPanel&p)
{
	if(!electricFurnace->canPushInItem(p.getID(),i))
		return 0;
	return BaseContainerScreenClassic::getAddItemToItemPanelCount(i,p);
}
void ElectricFurnaceScreenClassic::setUIProgress()
{
	ProgressController::setProcess(*mcGame,width/2-11,height/2-50,22,15,electricFurnace->getBurnProgress(),progress_filled,false);
	ProgressController::setEnergySmall(*mcGame,width/2-50,height/2-48,16,16,electricFurnace->getElectricProgress(),energyBackground_filled,false);
}
