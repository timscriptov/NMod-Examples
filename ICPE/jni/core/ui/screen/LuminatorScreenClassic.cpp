#include "LuminatorScreenClassic.h"

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

#include "blocks/blockentity/LuminatorBlockEntity.h"
#include "ui/ProgressController.h"

LuminatorScreenClassic::LuminatorScreenClassic(MinecraftGame&game,ClientInstance&client,Player&p,BlockPos const&pos_):BaseContainerScreenClassic(game,client,p.getRegion(),p,"te.luminator_flat")
{
	luminator=(LuminatorBlockEntity*)source.getBlockEntity(pos_);
	pos=pos_;
}
std::string LuminatorScreenClassic::getScreenName()const
{
	return "ic_luminator_screen";
}
std::string LuminatorScreenClassic::getScreenNameW()const
{
	return "ic_luminator_screen";
}
void LuminatorScreenClassic::_buttonClicked(Button&b)
{
	BaseContainerScreenClassic::_buttonClicked(b);
}
void LuminatorScreenClassic::onInit()
{
	storageMessage=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setEnergyLarge(*mcGame,width/2-20,height/2-30,40,30,1.0,storageMessage,true);
	tabElementList.emplace_back(storageMessage);
	
	storageMessageFilled=std::make_shared<GuiElement>(false,false,0,0,0,0);
	ProgressController::setEnergyLarge(*mcGame,width/2-20,height/2-30,40,30,1.0,storageMessageFilled,false);
	tabElementList.emplace_back(storageMessageFilled);
	
	setUIProgress();
}
void LuminatorScreenClassic::onRender()
{
	setUIProgress();
}
void LuminatorScreenClassic::onItemPanelChanged(ItemPanel&p)
{
	ItemInstance item=p.getItem();
	if(!item.isNull())
		luminator->setSlot(p.getID(),&item);
	else
		luminator->setSlot(p.getID(),0);
}
void LuminatorScreenClassic::onRegisterPanels()
{
	registerNewItemPanel(width/2-10,height/2-55,20,20,ItemInstance());
}
void LuminatorScreenClassic::tick()
{
	BaseContainerScreenClassic::tick();
	
	if(source.getBlockEntity(pos)!=luminator)
	{
		mcGame->getScreenChooser()->schedulePopScreen(1);
		return;
	}
	for(int i=0;i<1;++i)
	{
		if(luminator->getSlot(i))
			itemPanels[i]->item=*luminator->getSlot(i);
	}
}
unsigned char LuminatorScreenClassic::getAddItemToItemPanelCount(ItemInstance const&i,ItemPanel&p)
{
	if(!luminator->canPushInItem(i))
		return 0;
	return BaseContainerScreenClassic::getAddItemToItemPanelCount(i,p);
}
void LuminatorScreenClassic::setUIProgress()
{
	ProgressController::setEnergyLarge(*mcGame,width/2-20,height/2-30,40,30,luminator->getEnergyStorageProgress(),storageMessageFilled,false);
}
