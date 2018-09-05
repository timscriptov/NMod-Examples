#pragma once

#include "BaseContainerScreenPocket.h"

class MaceratorBlockEntity;

class MaceratorScreenPocket : public BaseContainerScreenPocket
{
private:
	MaceratorBlockEntity*macerator;
	BlockPos pos;
private:
	std::shared_ptr<GuiElement> energyBackground_empty;
	std::shared_ptr<GuiElement> energyBackground_filled;
	std::shared_ptr<GuiElement> progress_empty;
	std::shared_ptr<GuiElement> progress_filled;
public:
	MaceratorScreenPocket(MinecraftGame&,ClientInstance&,Player&,BlockPos const&);
	~MaceratorScreenPocket()=default;
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
