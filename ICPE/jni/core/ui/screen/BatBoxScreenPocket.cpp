#include "BatBoxScreenPocket.h"

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

BatBoxScreenPocket::BatBoxScreenPocket(MinecraftGame&game,ClientInstance&client,Player&p,BlockPos const&pos_):BaseContainerScreenPocket(game,client,p.getRegion(),p,"te.batbox")
{
	batbox=(BatBoxBlockEntity*)source.getBlockEntity(pos_);
	pos=pos_;
}
std::string BatBoxScreenPocket::getScreenName()const
{
	return "ic_batbox_screen";
}
std::string BatBoxScreenPocket::getScreenNameW()const
{
	return "ic_batbox_screen";
}
void BatBoxScreenPocket::_buttonClicked(Button&b)
{
	BaseContainerScreenPocket::_buttonClicked(b);
}
void BatBoxScreenPocket::onInit()
{
	progress_empty=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setEnergyLarge(*mcGame,35+width/2+((width/2-120)/2),height/2-10,36,20,1.0,progress_empty,true);
	tabElementList.emplace_back(progress_empty);
	
	progress_filled=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setEnergyLarge(*mcGame,35+width/2+((width/2-120)/2),height/2-10,36,20,1.0,progress_filled,false);
	tabElementList.emplace_back(progress_filled);
	
	setUIProgress();
}
void BatBoxScreenPocket::onRender()
{
	setUIProgress();
}
void BatBoxScreenPocket::onItemPanelChanged(ItemPanel&p)
{
	ItemInstance item=p.getItem();
	if(!item.isNull())
		batbox->setSlot(p.getID(),&item);
	else
		batbox->setSlot(p.getID(),0);
}
void BatBoxScreenPocket::onRegisterPanels()
{
	registerNewItemPanel(width/2,height/2-60,30,30,ItemInstance());
	registerNewItemPanel(width/2,height/2+25,30,30,ItemInstance());
}
void BatBoxScreenPocket::tick()
{
	BaseContainerScreenPocket::tick();
	
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
unsigned char BatBoxScreenPocket::getAddItemToItemPanelCount(ItemInstance const&i,ItemPanel&p)
{
	if(!batbox->canPushInItem(p.getID(),i))
		return 0;
	return BaseContainerScreenPocket::getAddItemToItemPanelCount(i,p);
}
void BatBoxScreenPocket::setUIProgress()
{
	ProgressController::setEnergyLarge(*mcGame,35+width/2+((width/2-120)/2),height/2-10,36,20,batbox->getEnergyProgress(),progress_filled,false);
}
