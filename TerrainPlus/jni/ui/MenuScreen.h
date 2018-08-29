#pragma once

#include "mcpe/client/gui/screen/Screen.h"

#include <memory>

class GuiElement;
class CloseButton;

class MenuScreen : public Screen
{
private:
	std::string mTitle;
	int mMenuWidth;
	int mMenuHeight;
	std::shared_ptr<GuiElement> mBackground;
	std::shared_ptr<GuiElement> mDarkBackground;
	std::shared_ptr<CloseButton> mCloseButton;
public:
	MenuScreen(MinecraftGame&,ClientInstance&,std::string const&title,int width,int height);
	~MenuScreen() = default;
public:
	virtual void render(int, int, float);
	virtual std::string getScreenName() const;
	virtual void init();
	virtual void setupPositions();
	virtual void _buttonClicked(Button&);
protected:
	int getMenuXPosition()const;
	int getMenuYPosition()const;
	int getMenuWidth()const;
	int getMenuHeight()const;
};
