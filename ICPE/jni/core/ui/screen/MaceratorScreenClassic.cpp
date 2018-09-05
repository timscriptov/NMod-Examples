#include "MaceratorScreenClassic.h"

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

#include "blocks/blockentity/MaceratorBlockEntity.h"
#include "ui/ProgressController.h"

MaceratorScreenClassic::MaceratorScreenClassic(MinecraftGame&game,ClientInstance&client,Player&p,BlockPos const&pos_):BaseContainerScreenClassic(game,client,p.getRegion(),p,"Macerator.gui.name")
{
	macerator=(MaceratorBlockEntity*)source.getBlockEntity(pos_);
	pos=pos_;
}
std::string MaceratorScreenClassic::getScreenName()const
{
	return "ic_macerator_screen";
}
std::string MaceratorScreenClassic::getScreenNameW()const
{
	return "ic_macerator_screen";
}
void MaceratorScreenClassic::_buttonClicked(Button&b)
{
	BaseContainerScreenClassic::_buttonClicked(b);
}
void MaceratorScreenClassic::onInit()
{
	energyBackground_empty=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setEnergySmall(*mcGame,width/2-50,height/2-48,16,16,1.0,energyBackground_empty,true);
	tabElementList.emplace_back(energyBackground_empty);
	
	energyBackground_filled=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setEnergySmall(*mcGame,width/2-50,height/2-48,16,16,1.0,energyBackground_filled,false);
	tabElementList.emplace_back(energyBackground_filled);
	
	progress_empty=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setMacerate(*mcGame,width/2-11,height/2-50,22,15,1.0,progress_empty,true);
	tabElementList.emplace_back(progress_empty);
	
	progress_filled=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setMacerate(*mcGame,width/2-11,height/2-50,22,15,1.0,progress_filled,false);
	tabElementList.emplace_back(progress_filled);
	
	setUIProgress();
}
void MaceratorScreenClassic::onRender()
{
	setUIProgress();
}
void MaceratorScreenClassic::onItemPanelChanged(ItemPanel&p)
{
	ItemInstance item=p.getItem();
	if(!item.isNull())
		macerator->setSlot(p.getID(),&item);
	else
		macerator->setSlot(p.getID(),0);
}
void MaceratorScreenClassic::onRegisterPanels()
{
	registerNewItemPanel(width/2-53,height/2-72,20,20,ItemInstance());
	registerNewItemPanel(width/2-53,height/2-29,20,20,ItemInstance());
	registerNewItemPanel(width/2+22,height/2-53,20,20,ItemInstance());
}
void MaceratorScreenClassic::tick()
{
	BaseContainerScreenClassic::tick();
	
	if(source.getBlockEntity(pos)!=macerator)
	{
		mcGame->getScreenChooser()->schedulePopScreen(1);
		return;
	}
	for(int i=0;i<3;++i)
	{
		if(macerator->getSlot(i))
			itemPanels[i]->item=*macerator->getSlot(i);
	}
}
unsigned char MaceratorScreenClassic::getAddItemToItemPanelCount(ItemInstance const&i,ItemPanel&p)
{
	if(!macerator->canPushInItem(p.getID(),i))
		return 0;
	return BaseContainerScreenClassic::getAddItemToItemPanelCount(i,p);
}
void MaceratorScreenClassic::setUIProgress()
{
	ProgressController::setMacerate(*mcGame,width/2-11,height/2-50,22,15,macerator->getWorkProgress(),progress_filled,false);
	ProgressController::setEnergySmall(*mcGame,width/2-50,height/2-48,16,16,macerator->getElectricProgress(),energyBackground_filled,false);
}
