#include "CompressorScreenClassic.h"

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

#include "blocks/blockentity/CompressorBlockEntity.h"
#include "ui/ProgressController.h"

CompressorScreenClassic::CompressorScreenClassic(MinecraftGame&game,ClientInstance&client,Player&p,BlockPos const&pos_):BaseContainerScreenClassic(game,client,p.getRegion(),p,"Compressor.gui.name")
{
	compressor=(CompressorBlockEntity*)source.getBlockEntity(pos_);
	pos=pos_;
}
std::string CompressorScreenClassic::getScreenName()const
{
	return "ic_compressor_screen";
}
std::string CompressorScreenClassic::getScreenNameW()const
{
	return "ic_compressor_screen";
}
void CompressorScreenClassic::_buttonClicked(Button&b)
{
	BaseContainerScreenClassic::_buttonClicked(b);
}
void CompressorScreenClassic::onInit()
{
	energyBackground_empty=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setEnergySmall(*mcGame,width/2-50,height/2-48,16,16,1.0,energyBackground_empty,true);
	tabElementList.emplace_back(energyBackground_empty);
	
	energyBackground_filled=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setEnergySmall(*mcGame,width/2-50,height/2-48,16,16,1.0,energyBackground_filled,false);
	tabElementList.emplace_back(energyBackground_filled);
	
	progress_empty=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setCompress(*mcGame,width/2-15,height/2-50,30,23,1.0,progress_empty,true);
	tabElementList.emplace_back(progress_empty);
	
	progress_filled=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setCompress(*mcGame,width/2-15,height/2-50,30,23,1.0,progress_filled,false);
	tabElementList.emplace_back(progress_filled);
	
	setUIProgress();
}
void CompressorScreenClassic::onRender()
{
	setUIProgress();
}
void CompressorScreenClassic::onItemPanelChanged(ItemPanel&p)
{
	ItemInstance item=p.getItem();
	if(!item.isNull())
		compressor->setSlot(p.getID(),&item);
	else
		compressor->setSlot(p.getID(),0);
}
void CompressorScreenClassic::onRegisterPanels()
{
	registerNewItemPanel(width/2-53,height/2-72,20,20,ItemInstance());
	registerNewItemPanel(width/2-53,height/2-29,20,20,ItemInstance());
	registerNewItemPanel(width/2+22,height/2-53,20,20,ItemInstance());
}
void CompressorScreenClassic::tick()
{
	BaseContainerScreenClassic::tick();
	
	if(source.getBlockEntity(pos)!=compressor)
	{
		mcGame->getScreenChooser()->schedulePopScreen(1);
		return;
	}
	for(int i=0;i<3;++i)
	{
		if(compressor->getSlot(i))
			itemPanels[i]->item=*compressor->getSlot(i);
	}
}
unsigned char CompressorScreenClassic::getAddItemToItemPanelCount(ItemInstance const&i,ItemPanel&p)
{
	if(!compressor->canPushInItem(p.getID(),i))
		return 0;
	return BaseContainerScreenClassic::getAddItemToItemPanelCount(i,p);
}
void CompressorScreenClassic::setUIProgress()
{
	ProgressController::setEnergySmall(*mcGame,width/2-50,height/2-48,16,16,compressor->getElectricProgress(),energyBackground_filled,false);
	ProgressController::setCompress(*mcGame,width/2-15,height/2-50,30,23,compressor->getWorkProgress(),progress_filled,false);
}
