#include "MenuScreen.h"

#include "elements/CloseButton.h"

#include "mcpe/client/gui/GuiData.h"
#include "mcpe/client/gui/IntRectangle.h"
#include "mcpe/client/gui/Font.h"
#include "mcpe/client/renderer/ScreenRenderer.h"
#include "mcpe/client/resources/I18n.h"
#include "mcpe/client/MinecraftGame.h"
#include "mcpe/util/Color.h"

MenuScreen::MenuScreen(MinecraftGame&game,ClientInstance&instance,std::string const&title,int width,int height)
:Screen(game,instance)
{
	mMenuWidth = width;
	mMenuHeight = height;
	mTitle = title;
}
void MenuScreen::render(int int1, int int2, float f)
{
	Screen::render(int1,int2,f);
	
	ScreenRenderer::singletonPtr->drawCenteredString(mcGame->getFont(),I18n::get(mTitle),width / 2,height / 2 - mMenuHeight / 2 + 10,Color::GREY);
}
std::string MenuScreen::getScreenName() const
{
	return "menu_screen";//menu_screen
}
void MenuScreen::init()
{
	mDarkBackground = std::make_shared<GuiElement>(false,false,0,0,0,0);
	mDarkBackground->setBackground(Color(0.0F,0.0F,0.0F,0.65F));
	tabElementList.push_back(mDarkBackground);
	
	mBackground = std::make_shared<GuiElement>(false,false,0,0,0,0);
	mBackground->setBackground(mcGame,"resource_packs/vanilla/textures/gui/newgui/NormalButtonNoStroke",{0,0,10,10},4,4);
	tabElementList.push_back(mBackground);
	
	mCloseButton = std::make_shared<CloseButton>(5225);
	buttonList.push_back(mCloseButton);
}
void MenuScreen::setupPositions()
{
	Screen::setupPositions();
	
	mDarkBackground->xPosition=0;
	mDarkBackground->yPosition=0;
	mDarkBackground->width=width;
	mDarkBackground->height=height;
	
	mBackground->xPosition = width / 2 - mMenuWidth / 2;
	mBackground->yPosition = height / 2 - mMenuHeight / 2;
	mBackground->width = mMenuWidth;
	mBackground->height = mMenuHeight;
	
	mCloseButton->xPosition = width / 2 + mMenuWidth / 2 - 25;
	mCloseButton->yPosition = height / 2 - mMenuHeight / 2 + 5;
	mCloseButton->width = 20;
	mCloseButton->height = 20;
}
void MenuScreen::_buttonClicked(Button&button)
{
	Screen::_buttonClicked(button);
	
	if(&button == mCloseButton.get())
	{
		mcGame->schedulePopScreen(1);
	}
}
int MenuScreen::getMenuXPosition()const
{
	return width / 2 - mMenuWidth / 2;
}
int MenuScreen::getMenuYPosition()const
{
	return height / 2 - mMenuHeight / 2;
}
int MenuScreen::getMenuWidth()const
{
	return mMenuWidth;
}
int MenuScreen::getMenuHeight()const
{
	return mMenuHeight;
}
