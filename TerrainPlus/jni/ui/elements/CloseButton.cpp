#include "CloseButton.h"

#include "mcpe/client/gui/IntRectangle.h"

CloseButton::CloseButton(int id)
:Button(id,"",false)
{
	mXView = std::make_shared<GuiElement>(false,false,0,0,0,0);
}
void CloseButton::render(MinecraftGame*game, int i1, int i2)
{
	mXView -> setBackground(game,pressed?"resource_packs/vanilla/textures/gui/newgui/XPress":"resource_packs/vanilla/textures/gui/newgui/X",{0,0,16,16},0,0);
	mXView -> xPosition = xPosition;
	mXView -> yPosition = yPosition;
	mXView -> width = width;
	mXView -> height = height;
	mXView -> render(game,i1,i2);
}
