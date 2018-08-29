#pragma once

#include <memory>

#include "mcpe/client/gui/Button.h"

class TabButton : public Button
{
private:
	std::shared_ptr<GuiElement> mView;
public:
	TabButton(int,std::string const&);
public:
	virtual void render(MinecraftGame*, int, int);
};
