#pragma once

#include "BaseContainerScreenPocket.h"

class SolarGeneratorBlockEntity;

class SolarGeneratorScreenPocket : public BaseContainerScreenPocket
{
private:
	SolarGeneratorBlockEntity*solarGenerator;
	BlockPos pos;
private:
	std::shared_ptr<GuiElement> activeMessage;
public:
	SolarGeneratorScreenPocket(MinecraftGame&,ClientInstance&,Player&,BlockPos const&);
	~SolarGeneratorScreenPocket()=default;
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
