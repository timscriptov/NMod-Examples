#pragma once

#include "BaseContainerScreenPocket.h"

class ElectricFurnaceBlockEntity;

class ElectricFurnaceScreenPocket : public BaseContainerScreenPocket
{
private:
	ElectricFurnaceBlockEntity*electricFurnace;
	BlockPos pos;
private:
	std::shared_ptr<GuiElement> energyBackground_empty;
	std::shared_ptr<GuiElement> energyBackground_filled;
	std::shared_ptr<GuiElement> progress_empty;
	std::shared_ptr<GuiElement> progress_filled;
public:
	ElectricFurnaceScreenPocket(MinecraftGame&,ClientInstance&,Player&,BlockPos const&);
	~ElectricFurnaceScreenPocket()=default;
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
