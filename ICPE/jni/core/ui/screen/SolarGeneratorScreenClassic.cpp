#include "SolarGeneratorScreenClassic.h"

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

SolarGeneratorScreenClassic::SolarGeneratorScreenClassic(MinecraftGame&game,ClientInstance&client,Player&p,BlockPos const&pos_):BaseContainerScreenClassic(game,client,p.getRegion(),p,"SolarGenerator.gui.name")
{
	solarGenerator=(SolarGeneratorBlockEntity*)source.getBlockEntity(pos_);
	pos=pos_;
}
std::string SolarGeneratorScreenClassic::getScreenName()const
{
	return "ic_solar_generator_screen";
}
std::string SolarGeneratorScreenClassic::getScreenNameW()const
{
	return "ic_solar_generator_screen";
}
void SolarGeneratorScreenClassic::_buttonClicked(Button&b)
{
	BaseContainerScreenClassic::_buttonClicked(b);
}
void SolarGeneratorScreenClassic::onInit()
{
	activeMessage=std::make_shared<GuiElement>(false,false,0,0,0,0);
	activeMessage->xPosition=width/2-8;
	activeMessage->yPosition=height/2-23;
	activeMessage->width=16;
	activeMessage->height=16;
	tabElementList.emplace_back(activeMessage);
	
	setUIProgress();
}
void SolarGeneratorScreenClassic::onRender()
{
	setUIProgress();
}
void SolarGeneratorScreenClassic::onItemPanelChanged(ItemPanel&p)
{
	ItemInstance item=p.getItem();
	if(!item.isNull())
		solarGenerator->setSlot(p.getID(),&item);
	else
		solarGenerator->setSlot(p.getID(),0);
}
void SolarGeneratorScreenClassic::onRegisterPanels()
{
	registerNewItemPanel(width/2-10,height/2-55,20,20,ItemInstance());
}
void SolarGeneratorScreenClassic::tick()
{
	BaseContainerScreenClassic::tick();
	
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
unsigned char SolarGeneratorScreenClassic::getAddItemToItemPanelCount(ItemInstance const&i,ItemPanel&p)
{
	if(!solarGenerator->canPushInItem(i))
		return 0;
	return BaseContainerScreenClassic::getAddItemToItemPanelCount(i,p);
}
void SolarGeneratorScreenClassic::setUIProgress()
{
	if(solarGenerator->isActive())
		activeMessage->setBackground(mcGame,"images/icpeui/sun",{12,12,8,8},0,0);
	else
		activeMessage->setBackground(mcGame,"images/icpeui/moon_phases",{12,12,8,8},0,0);
}
