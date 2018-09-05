#include "RendererStack.h"

void RendererStack::show(std::shared_ptr<BaseFloatingMenuRenderer>r)
{
	if(!r.get())
		return;
	r->init();
	rendererStack.emplace_back(r);
}
void RendererStack::render()
{
	for(std::shared_ptr<BaseFloatingMenuRenderer> renderer:rendererStack)
	{
		if(renderer.get()&&renderer->isFinished())
		{
			renderer.reset();
		}
		else if(renderer.get())
		{
			renderer->setupPositions();
			renderer->render();
		}
	}
}
