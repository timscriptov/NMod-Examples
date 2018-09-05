#include "ExtractorScreenClassic.h"

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

#include "blocks/blockentity/ExtractorBlockEntity.h"
#include "ui/ProgressController.h"

ExtractorScreenClassic::ExtractorScreenClassic(MinecraftGame&game,ClientInstance&client,Player&p,BlockPos const&pos_):BaseContainerScreenClassic(game,client,p.getRegion(),p,"Extractor.gui.name")
{
	extractor=(ExtractorBlockEntity*)source.getBlockEntity(pos_);
	pos=pos_;
}
std::string ExtractorScreenClassic::getScreenName()const
{
	return "ic_extractor_screen";
}
std::string ExtractorScreenClassic::getScreenNameW()const
{
	return "ic_extractor_screen";
}
void ExtractorScreenClassic::_buttonClicked(Button&b)
{
	BaseContainerScreenClassic::_buttonClicked(b);
}
void ExtractorScreenClassic::onInit()
{
	energyBackground_empty=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setEnergySmall(*mcGame,width/2-50,height/2-48,16,16,1.0,energyBackground_empty,true);
	tabElementList.emplace_back(energyBackground_empty);
	
	energyBackground_filled=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setEnergySmall(*mcGame,width/2-50,height/2-48,16,16,1.0,energyBackground_filled,false);
	tabElementList.emplace_back(energyBackground_filled);
	
	progress_empty=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setExtracte(*mcGame,width/2-15,height/2-50,30,23,1.0,progress_empty,true);
	tabElementList.emplace_back(progress_empty);
	
	progress_filled=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setExtracte(*mcGame,width/2-15,height/2-50,30,23,1.0,progress_filled,false);
	tabElementList.emplace_back(progress_filled);
	
	setUIProgress();
}
void ExtractorScreenClassic::onRender()
{
	setUIProgress();
}
void ExtractorScreenClassic::onItemPanelChanged(ItemPanel&p)
{
	ItemInstance item=p.getItem();
	if(!item.isNull())
		extractor->setSlot(p.getID(),&item);
	else
		extractor->setSlot(p.getID(),0);
}
void ExtractorScreenClassic::onRegisterPanels()
{
	registerNewItemPanel(width/2-53,height/2-72,20,20,ItemInstance());
	registerNewItemPanel(width/2-53,height/2-29,20,20,ItemInstance());
	registerNewItemPanel(width/2+22,height/2-53,20,20,ItemInstance());
}
void ExtractorScreenClassic::tick()
{
	BaseContainerScreenClassic::tick();
	
	if(source.getBlockEntity(pos)!=extractor)
	{
		mcGame->getScreenChooser()->schedulePopScreen(1);
		return;
	}
	for(int i=0;i<3;++i)
	{
		if(extractor->getSlot(i))
			itemPanels[i]->item=*extractor->getSlot(i);
	}
}
unsigned char ExtractorScreenClassic::getAddItemToItemPanelCount(ItemInstance const&i,ItemPanel&p)
{
	if(!extractor->canPushInItem(p.getID(),i))
		return 0;
	return BaseContainerScreenClassic::getAddItemToItemPanelCount(i,p);
}
void ExtractorScreenClassic::setUIProgress()
{
	ProgressController::setEnergySmall(*mcGame,width/2-50,height/2-48,16,16,extractor->getElectricProgress(),energyBackground_filled,false);
	ProgressController::setExtracte(*mcGame,width/2-15,height/2-50,30,23,extractor->getWorkProgress(),progress_filled,false);
}
