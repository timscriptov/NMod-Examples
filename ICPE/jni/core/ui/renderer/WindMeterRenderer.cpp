#include "WindMeterRenderer.h"

#include "mcpe/client/resources/I18n.h"
#include "mcpe/client/renderer/ScreenRenderer.h"
#include "mcpe/client/gui/Font.h"
#include "mcpe/client/MinecraftGame.h"
#include "mcpe/util/Util.h"

WindMeterRenderer::WindMeterRenderer(MinecraftGame&client,float v)
:BaseFloatingMenuRenderer(client,25)
{
	value=v;
}
void WindMeterRenderer::render()
{
	BaseFloatingMenuRenderer::render();
	
	mcGame->getFont()->drawShadow(I18n::get("itemwindmeter.info",{Util::toFloatString(value)}),xPosition+5,yPosition+7.5,Color::WHITE,false,0);
}
void WindMeterRenderer::init()
{
	BaseFloatingMenuRenderer::init();
	
	setTime(1000);
}
void WindMeterRenderer::setupPositions()
{
	BaseFloatingMenuRenderer::setupPositions();
}
