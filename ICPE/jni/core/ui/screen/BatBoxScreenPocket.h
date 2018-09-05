#pragma once

#include "BaseContainerScreenPocket.h"

class BatBoxBlockEntity;

class BatBoxScreenPocket : public BaseContainerScreenPocket
{
private:
	BatBoxBlockEntity*batbox;
	BlockPos pos;
private:
	std::shared_ptr<GuiElement> progress_empty;
	std::shared_ptr<GuiElement> progress_filled;
public:
	BatBoxScreenPocket(MinecraftGame&,ClientInstance&,Player&,BlockPos const&);
	~BatBoxScreenPocket()=default;
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
