#pragma once

#include "BaseContainerScreenClassic.h"

class ElectricFurnaceBlockEntity;

class ElectricFurnaceScreenClassic : public BaseContainerScreenClassic
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
	ElectricFurnaceScreenClassic(MinecraftGame&,ClientInstance&,Player&,BlockPos const&);
	~ElectricFurnaceScreenClassic()=default;
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
