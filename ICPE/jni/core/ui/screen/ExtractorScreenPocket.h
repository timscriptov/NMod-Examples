#pragma once

#include "BaseContainerScreenPocket.h"

class ExtractorBlockEntity;

class ExtractorScreenPocket : public BaseContainerScreenPocket
{
private:
	ExtractorBlockEntity*extractor;
	BlockPos pos;
private:
	std::shared_ptr<GuiElement> energyBackground_empty;
	std::shared_ptr<GuiElement> energyBackground_filled;
	std::shared_ptr<GuiElement> progress_empty;
	std::shared_ptr<GuiElement> progress_filled;
public:
	ExtractorScreenPocket(MinecraftGame&,ClientInstance&,Player&,BlockPos const&);
	~ExtractorScreenPocket()=default;
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
