#pragma once

#include "BaseContainerScreenClassic.h"

class SolarGeneratorBlockEntity;

class SolarGeneratorScreenClassic : public BaseContainerScreenClassic
{
private:
	SolarGeneratorBlockEntity*solarGenerator;
	BlockPos pos;
private:
	std::shared_ptr<GuiElement> activeMessage;
public:
	SolarGeneratorScreenClassic(MinecraftGame&,ClientInstance&,Player&,BlockPos const&);
	~SolarGeneratorScreenClassic()=default;
public:
	virtual std::string getScreenName()const;
	virtual std::string getScreenNameW()const;
	virtual void _buttonClicked(Button&);
	virtual void onInit();
    virtual void tick();
	virtual void onRender();
	virtual void onItemPanelChanged(ItemPanel&);
	virtual void onRegisterPanels();
	virtual unsigned char getAddItemToItemPanelCount(ItemInstance const&,ItemPanel&);
public:
	void setUIProgress();
};
