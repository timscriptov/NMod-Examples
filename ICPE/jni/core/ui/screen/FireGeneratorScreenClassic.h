#pragma once

#include "BaseContainerScreenClassic.h"

class FireGeneratorBlockEntity;

class FireGeneratorScreenClassic : public BaseContainerScreenClassic
{
private:
	FireGeneratorBlockEntity*generator;
	BlockPos pos;
private:
	std::shared_ptr<GuiElement> fireBackground_empty;
	std::shared_ptr<GuiElement> fireBackground_filled;
	std::shared_ptr<GuiElement> progress_empty;
	std::shared_ptr<GuiElement> progress_filled;
public:
	FireGeneratorScreenClassic(MinecraftGame&,ClientInstance&,Player&,BlockPos const&);
	~FireGeneratorScreenClassic()=default;
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
