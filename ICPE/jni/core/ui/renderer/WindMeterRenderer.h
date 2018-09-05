#pragma once

#include "BaseFloatingMenuRenderer.h"

class WindMeterRenderer : public BaseFloatingMenuRenderer
{
private:
	float value;
public:
	WindMeterRenderer(MinecraftGame&,float);
	virtual void render();
	virtual void init();
	virtual void setupPositions();
};
