#include "BaseFloatingMenuRenderer.h"

#include "ICPE.h"
#include "RendererStack.h"
#include "mcpe/client/gui/GuiData.h"
#include "mcpe/client/gui/IntRectangle.h"
#include "mcpe/client/MinecraftGame.h"
#include "mcpe/client/renderer/ScreenRenderer.h"
#include "mcpe/client/resources/I18n.h"
#include "mcpe/util/Color.h"

BaseFloatingMenuRenderer::BaseFloatingMenuRenderer(MinecraftGame&c,float h)
{
	mcGame=&c;
	width=mcGame->getScreenWidth()/2;
	xPosition=mcGame->getScreenWidth()/2;
	height=h;
	yPosition=-h;
}
void BaseFloatingMenuRenderer::render()
{
	if(yPosition<0&&time>0)
		yPosition+=1;
	else if(yPosition>=0&&time>0)
		--time;
	else if(time<=0)
		yPosition-=1;
	
	if(background.get())
		background->render(mcGame,background->xPosition,background->yPosition);
}
void BaseFloatingMenuRenderer::init()
{
	background=std::make_shared<GuiElement>(false,false,0,0,0,0);
	background->xPosition=xPosition;
	background->yPosition=yPosition;
	background->width=width;
	background->height=height;
	background->setBackground(mcGame,"textures/gui/greyBorder",IntRectangle{0,0,16,16},4,4);
}
void BaseFloatingMenuRenderer::setupPositions()
{
	xPosition=mcGame->getGuiData()->getScreenWidth()/2;
	width=mcGame->getGuiData()->getScreenWidth()/2;
	
	background->xPosition=xPosition;
	background->yPosition=yPosition;
	background->width=width;
	background->height=height;
}
void BaseFloatingMenuRenderer::show()
{
	ICPE::mRendererStack.show(std::shared_ptr<BaseFloatingMenuRenderer>(this));
}
bool BaseFloatingMenuRenderer::operator==(BaseFloatingMenuRenderer const&r)const
{
	return this==&r;
}
void BaseFloatingMenuRenderer::setTime(int t)
{
	time=t;
}
bool BaseFloatingMenuRenderer::isFinished()
{
	return (-yPosition)>height&&time<=0;
}
