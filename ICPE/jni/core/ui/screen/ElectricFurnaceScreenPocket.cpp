#include "ElectricFurnaceScreenPocket.h"

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

ElectricFurnaceScreenPocket::ElectricFurnaceScreenPocket(MinecraftGame&game,ClientInstance&client,Player&p,BlockPos const&pos_):BaseContainerScreenPocket(game,client,p.getRegion(),p,"ElecFurnace.gui.name")
{
	electricFurnace=(ElectricFurnaceBlockEntity*)source.getBlockEntity(pos_);
	pos=pos_;
}
std::string ElectricFurnaceScreenPocket::getScreenName()const
{
	return "ic_furnace_electric_screen";
}
std::string ElectricFurnaceScreenPocket::getScreenNameW()const
{
	return "ic_furnace_electric_screen";
}
void ElectricFurnaceScreenPocket::_buttonClicked(Button&b)
{
	BaseContainerScreenPocket::_buttonClicked(b);
}
void ElectricFurnaceScreenPocket::onInit()
{
	energyBackground_empty=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setEnergySmall(*mcGame,width/2+7,height/2-10,20,20,1.0,energyBackground_empty,true);
	tabElementList.emplace_back(energyBackground_empty);
	
	energyBackground_filled=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setEnergySmall(*mcGame,width/2+7,height/2-10,20,20,1.0,energyBackground_filled,false);
	tabElementList.emplace_back(energyBackground_filled);
	
	progress_empty=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setProcess(*mcGame,35+width/2+((width/2-120)/2),height/2-10,36,20,1.0,progress_empty,true);
	tabElementList.emplace_back(progress_empty);
	
	progress_filled=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setProcess(*mcGame,35+width/2+((width/2-120)/2),height/2-10,36,20,1.0,progress_filled,false);
	tabElementList.emplace_back(progress_filled);
	
	setUIProgress();
}
void ElectricFurnaceScreenPocket::onRender()
{
	setUIProgress();
}
void ElectricFurnaceScreenPocket::onItemPanelChanged(ItemPanel&p)
{
	ItemInstance item=p.getItem();
	if(!item.isNull())
		electricFurnace->setSlot(p.getID(),&item);
	else
		electricFurnace->setSlot(p.getID(),0);
}
void ElectricFurnaceScreenPocket::onRegisterPanels()
{
	registerNewItemPanel(width/2,height/2-60,30,30,ItemInstance());
	registerNewItemPanel(width/2,height/2+25,30,30,ItemInstance());
	registerNewItemPanel(width-50,height/2-17,30,30,ItemInstance());
}
void ElectricFurnaceScreenPocket::tick()
{
	BaseContainerScreenPocket::tick();
	
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
unsigned char ElectricFurnaceScreenPocket::getAddItemToItemPanelCount(ItemInstance const&i,ItemPanel&p)
{
	if(!electricFurnace->canPushInItem(p.getID(),i))
		return 0;
	return BaseContainerScreenPocket::getAddItemToItemPanelCount(i,p);
}
void ElectricFurnaceScreenPocket::setUIProgress()
{
	ProgressController::setEnergySmall(*mcGame,width/2+7,height/2-10,20,20,electricFurnace->getElectricProgress(),energyBackground_filled,false);
	ProgressController::setProcess(*mcGame,35+width/2+((width/2-120)/2),height/2-10,36,20,electricFurnace->getBurnProgress(),progress_filled,false);
}
