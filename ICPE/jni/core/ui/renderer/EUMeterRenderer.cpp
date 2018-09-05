#include "EUMeterRenderer.h"

EUMeterRenderer::EUMeterRenderer(MinecraftGame&client,Energy const&e1,Energy const&e2)
:BaseFloatingMenuRenderer(client,50)
{
	defaultValue=e1;
	maxValue=e2;
}
void EUMeterRenderer::render()
{
	BaseFloatingMenuRenderer::render();
	
	
}
void EUMeterRenderer::init()
{
	BaseFloatingMenuRenderer::init();
	
	setTime(1000);
}
void EUMeterRenderer::setupPositions()
{
	BaseFloatingMenuRenderer::setupPositions();
}
