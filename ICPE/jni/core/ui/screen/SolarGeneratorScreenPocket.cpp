#include "SolarGeneratorScreenPocket.h"

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

#include "blocks/blockentity/SolarGeneratorBlockEntity.h"

SolarGeneratorScreenPocket::SolarGeneratorScreenPocket(MinecraftGame&game,ClientInstance&client,Player&p,BlockPos const&pos_):BaseContainerScreenPocket(game,client,p.getRegion(),p,"SolarGenerator.gui.name")
{
	solarGenerator=(SolarGeneratorBlockEntity*)source.getBlockEntity(pos_);
	pos=pos_;
}
std::string SolarGeneratorScreenPocket::getScreenName()const
{
	return "ic_solar_generator_screen";
}
std::string SolarGeneratorScreenPocket::getScreenNameW()const
{
	return "ic_solar_generator_screen";
}
void SolarGeneratorScreenPocket::_buttonClicked(Button&b)
{
	BaseContainerScreenPocket::_buttonClicked(b);
}
void SolarGeneratorScreenPocket::onInit()
{
	activeMessage=std::make_shared<GuiElement>(false,false,0,0,0,0);
	activeMessage->xPosition=width/2+width/4;
	activeMessage->yPosition=height/2-15;
	activeMessage->width=30;
	activeMessage->height=30;
	tabElementList.emplace_back(activeMessage);
	
	setUIProgress();
}
void SolarGeneratorScreenPocket::onRender()
{
	setUIProgress();
}
void SolarGeneratorScreenPocket::onItemPanelChanged(ItemPanel&p)
{
	ItemInstance item=p.getItem();
	if(!item.isNull())
		solarGenerator->setSlot(p.getID(),&item);
	else
		solarGenerator->setSlot(p.getID(),0);
}
void SolarGeneratorScreenPocket::onRegisterPanels()
{
	registerNewItemPanel(width/2+width/4-45,height/2-15,30,30,ItemInstance());
}
void SolarGeneratorScreenPocket::tick()
{
	BaseContainerScreenPocket::tick();
	
	if(source.getBlockEntity(pos)!=solarGenerator)
	{
		mcGame->getScreenChooser()->schedulePopScreen(1);
		return;
	}
	for(int i=0;i<1;++i)
	{
		if(solarGenerator->getSlot(i))
			itemPanels[i]->item=*solarGenerator->getSlot(i);
	}
}
unsigned char SolarGeneratorScreenPocket::getAddItemToItemPanelCount(ItemInstance const&i,ItemPanel&p)
{
	if(!solarGenerator->canPushInItem(i))
		return 0;
	return BaseContainerScreenPocket::getAddItemToItemPanelCount(i,p);
}
void SolarGeneratorScreenPocket::setUIProgress()
{
	if(solarGenerator->isActive())
		activeMessage->setBackground(mcGame,"images/icpeui/sun",{12,12,8,8},0,0);
	else
		activeMessage->setBackground(mcGame,"images/icpeui/moon_phases",{12,12,8,8},0,0);
}
