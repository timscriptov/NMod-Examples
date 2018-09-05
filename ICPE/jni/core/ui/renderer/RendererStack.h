#pragma once

#include <memory>
#include <vector>
#include "BaseFloatingMenuRenderer.h"

class RendererStack
{
private:
	std::vector<std::shared_ptr<BaseFloatingMenuRenderer> > rendererStack;
public:
	RendererStack()=default;
	~RendererStack()=default;
	void show(std::shared_ptr<BaseFloatingMenuRenderer>);
	void render();
};
