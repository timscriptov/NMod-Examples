#pragma once

#include "BaseContainerScreenClassic.h"

class BatBoxBlockEntity;

class BatBoxScreenClassic : public BaseContainerScreenClassic
{
private:
	BatBoxBlockEntity*batbox;
	BlockPos pos;
private:
	std::shared_ptr<GuiElement> progress_empty;
	std::shared_ptr<GuiElement> progress_filled;
public:
	BatBoxScreenClassic(MinecraftGame&,ClientInstance&,Player&,BlockPos const&);
	~BatBoxScreenClassic()=default;
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
