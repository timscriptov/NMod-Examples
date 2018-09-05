#pragma once

#include "BaseFloatingMenuRenderer.h"
#include "util/energy/Energy.h"

class EUMeterRenderer : public BaseFloatingMenuRenderer
{
private:
	Energy defaultValue;
	Energy maxValue;
public:
	EUMeterRenderer(MinecraftGame&,Energy const&,Energy const&);
	virtual void render();
	virtual void init();
	virtual void setupPositions();
};
