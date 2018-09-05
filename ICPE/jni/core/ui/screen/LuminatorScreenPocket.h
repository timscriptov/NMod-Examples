#pragma once

#include "BaseContainerScreenPocket.h"

class LuminatorBlockEntity;

class LuminatorScreenPocket : public BaseContainerScreenPocket
{
private:
	LuminatorBlockEntity*luminator;
	BlockPos pos;
private:
	std::shared_ptr<GuiElement> storageMessage;
	std::shared_ptr<GuiElement> storageMessageFilled;
public:
	LuminatorScreenPocket(MinecraftGame&,ClientInstance&,Player&,BlockPos const&);
	~LuminatorScreenPocket()=default;
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
