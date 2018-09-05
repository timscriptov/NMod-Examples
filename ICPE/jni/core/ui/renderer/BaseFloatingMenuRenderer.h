#pragma once

#include <memory>
#include "mcpe/client/gui/GuiElement.h"

class MinecraftGame;

class BaseFloatingMenuRenderer
{
protected:
	MinecraftGame* mcGame;
	float width;
	float height;
	float xPosition;
	float yPosition;
	int time;
	std::shared_ptr<GuiElement> background;
public:
	BaseFloatingMenuRenderer(MinecraftGame&,float);
	BaseFloatingMenuRenderer()=delete;
	~BaseFloatingMenuRenderer()=default;
public:
	virtual void render();
	virtual void init();
	virtual void setupPositions();
	virtual void show();
	bool operator==(BaseFloatingMenuRenderer const&)const;
	void setTime(int);
	bool isFinished();
};
