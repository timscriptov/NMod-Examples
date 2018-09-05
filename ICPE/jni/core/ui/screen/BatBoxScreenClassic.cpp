#include "BatBoxScreenClassic.h"

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

#include "blocks/blockentity/BatBoxBlockEntity.h"
#include "ui/ProgressController.h"

BatBoxScreenClassic::BatBoxScreenClassic(MinecraftGame&game,ClientInstance&client,Player&p,BlockPos const&pos_):BaseContainerScreenClassic(game,client,p.getRegion(),p,"te.batbox")
{
	batbox=(BatBoxBlockEntity*)source.getBlockEntity(pos_);
	pos=pos_;
}
std::string BatBoxScreenClassic::getScreenName()const
{
	return "ic_batbox_screen";
}
std::string BatBoxScreenClassic::getScreenNameW()const
{
	return "ic_batbox_screen";
}
void BatBoxScreenClassic::_buttonClicked(Button&b)
{
	BaseContainerScreenClassic::_buttonClicked(b);
}
void BatBoxScreenClassic::onInit()
{
	progress_empty=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setEnergyLarge(*mcGame,width/2-11,height/2-51,32,17,1.0,progress_empty,true);
	tabElementList.emplace_back(progress_empty);
	
	progress_filled=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setEnergyLarge(*mcGame,width/2-11,height/2-51,32,17,1.0,progress_filled,false);
	tabElementList.emplace_back(progress_filled);
	
	setUIProgress();
}
void BatBoxScreenClassic::onRender()
{
	setUIProgress();
}
void BatBoxScreenClassic::onItemPanelChanged(ItemPanel&p)
{
	ItemInstance item=p.getItem();
	if(!item.isNull())
		batbox->setSlot(p.getID(),&item);
	else
		batbox->setSlot(p.getID(),0);
}
void BatBoxScreenClassic::onRegisterPanels()
{
	registerNewItemPanel(width/2-53,height/2-72,20,20,ItemInstance());
	registerNewItemPanel(width/2-53,height/2-29,20,20,ItemInstance());
}
void BatBoxScreenClassic::tick()
{
	BaseContainerScreenClassic::tick();
	
	if(source.getBlockEntity(pos)!=batbox)
	{
		mcGame->getScreenChooser()->schedulePopScreen(1);
		return;
	}
	for(int i=0;i<2;++i)
	{
		if(batbox->getSlot(i))
			itemPanels[i]->item=*batbox->getSlot(i);
	}
}
unsigned char BatBoxScreenClassic::getAddItemToItemPanelCount(ItemInstance const&i,ItemPanel&p)
{
	if(!batbox->canPushInItem(p.getID(),i))
		return 0;
	return BaseContainerScreenClassic::getAddItemToItemPanelCount(i,p);
}
void BatBoxScreenClassic::setUIProgress()
{
	ProgressController::setEnergyLarge(*mcGame,width/2-11,height/2-51,32,17,batbox->getEnergyProgress(),progress_filled,false);
}
