#include "ExtractorScreenPocket.h"

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

ExtractorScreenPocket::ExtractorScreenPocket(MinecraftGame&game,ClientInstance&client,Player&p,BlockPos const&pos_):BaseContainerScreenPocket(game, client,p.getRegion(),p,"Extractor.gui.name")
{
	extractor=(ExtractorBlockEntity*)source.getBlockEntity(pos_);
	pos=pos_;
}
std::string ExtractorScreenPocket::getScreenName()const
{
	return "ic_extractor_screen";
}
std::string ExtractorScreenPocket::getScreenNameW()const
{
	return "ic_extractor_screen";
}
void ExtractorScreenPocket::_buttonClicked(Button&b)
{
	BaseContainerScreenPocket::_buttonClicked(b);
}
void ExtractorScreenPocket::onInit()
{
	energyBackground_empty=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setEnergySmall(*mcGame,width/2+7,height/2-10,20,20,1.0,energyBackground_empty,true);
	tabElementList.emplace_back(energyBackground_empty);
	
	energyBackground_filled=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setEnergySmall(*mcGame,width/2+7,height/2-10,20,20,1.0,energyBackground_filled,false);
	tabElementList.emplace_back(energyBackground_filled);
	
	progress_empty=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setExtracte(*mcGame,35+width/2+((width/2-120)/2),height/2-10,36,20,1.0,progress_empty,true);
	tabElementList.emplace_back(progress_empty);
	
	progress_filled=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setExtracte(*mcGame,35+width/2+((width/2-120)/2),height/2-10,36,20,1.0,progress_filled,false);
	tabElementList.emplace_back(progress_filled);
	
	setUIProgress();
}
void ExtractorScreenPocket::onRender()
{
	setUIProgress();
}
void ExtractorScreenPocket::onItemPanelChanged(ItemPanel&p)
{
	ItemInstance item=p.getItem();
	if(!item.isNull())
		extractor->setSlot(p.getID(),&item);
	else
		extractor->setSlot(p.getID(),0);
}
void ExtractorScreenPocket::onRegisterPanels()
{
	registerNewItemPanel(width/2,height/2-60,30,30,ItemInstance());
	registerNewItemPanel(width/2,height/2+25,30,30,ItemInstance());
	registerNewItemPanel(width-50,height/2-17,30,30,ItemInstance());
}
void ExtractorScreenPocket::tick()
{
	BaseContainerScreenPocket::tick();
	
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
unsigned char ExtractorScreenPocket::getAddItemToItemPanelCount(ItemInstance const&i,ItemPanel&p)
{
	if(!extractor->canPushInItem(p.getID(),i))
		return 0;
	return BaseContainerScreenPocket::getAddItemToItemPanelCount(i,p);
}
void ExtractorScreenPocket::setUIProgress()
{
	ProgressController::setEnergySmall(*mcGame,width/2+7,height/2-10,20,20,extractor->getElectricProgress(),energyBackground_filled,false);
	ProgressController::setExtracte(*mcGame,35+width/2+((width/2-120)/2),height/2-10,36,20,extractor->getWorkProgress(),progress_filled,false);
}
