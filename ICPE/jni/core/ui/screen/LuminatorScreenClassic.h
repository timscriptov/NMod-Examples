#pragma once

#include "BaseContainerScreenClassic.h"

class LuminatorBlockEntity;

class LuminatorScreenClassic : public BaseContainerScreenClassic
{
private:
	LuminatorBlockEntity*luminator;
	BlockPos pos;
private:
	std::shared_ptr<GuiElement> storageMessage;
	std::shared_ptr<GuiElement> storageMessageFilled;
public:
	LuminatorScreenClassic(MinecraftGame&,ClientInstance&,Player&,BlockPos const&);
	~LuminatorScreenClassic()=default;
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
