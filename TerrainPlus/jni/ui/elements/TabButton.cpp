#include "TabButton.h"

#include "mcpe/client/gui/IntRectangle.h"
#include "mcpe/client/renderer/ScreenRenderer.h"
#include "mcpe/client/resources/I18n.h"
#include "mcpe/client/MinecraftGame.h"

TabButton::TabButton(int id,std::string const&msg)
:Button(id,msg,false)
{
	mView = std::make_shared<GuiElement>(false,false,0,0,0,0);
}
void TabButton::render(MinecraftGame*game, int i1, int i2)
{
	mView -> setBackground(game,pressed?"textures/gui/newgui/ButtonWithBorderPressed":"textures/gui/newgui/ButtonWithBorder",{0,0,6,6},2,2);
	mView -> xPosition = xPosition;
	mView -> yPosition = yPosition;
	mView -> width = width;
	mView -> height = height;
	mView -> render(game,i1,i2);
	
	ScreenRenderer::singletonPtr->drawCenteredString(game->getFont(),I18n::get(msg),xPosition + width / 2,yPosition + height / 2 - 4 + (pressed?1:0),pressed?Color::WHITE:Color::GREY);
}
