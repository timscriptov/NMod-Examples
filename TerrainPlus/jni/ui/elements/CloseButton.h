#pragma once

#include <memory>

#include "mcpe/client/gui/Button.h"

class CloseButton : public Button
{
private:
	std::shared_ptr<GuiElement> mXView;
public:
	CloseButton(int);
public:
	virtual void render(MinecraftGame*, int, int);
};
