#include "SidebarManager.h"

#include "mcpe/item/ItemInstance.h"

#define SIDEBAR_HEIGHT 35
#define SIDEBAR_WIDTH 185

SidebarManager::SidebarManager(MinecraftGame&game)
{
	mMinecraftGame = &game;
}
bool SidebarManager::showNewSidebar(std::string const&title,std::string const&summary,ItemInstance const&item)
{
	if(!mMinecraftGame)
		return false;
	
	char index = -1;
	if(!mSidebar0.get())
		index = 0;
	else if(!mSidebar1.get())
		index = 1;
	else if(!mSidebar2.get())
		index = 2;
	else if(!mSidebar3.get())
		index = 3;
	else if(!mSidebar4.get())
		index = 4;
	else
		return false;
	std::shared_ptr<Sidebar> newSideBar = std::make_shared<Sidebar>(*mMinecraftGame,index * SIDEBAR_HEIGHT,SIDEBAR_WIDTH,SIDEBAR_HEIGHT,title,summary,item);
	switch(index)
	{
	case 0:
		mSidebar0 = newSideBar;
		break;
	case 1:
		mSidebar1 = newSideBar;
		break;
	case 2:
		mSidebar2 = newSideBar;
		break;
	case 3:
		mSidebar3 = newSideBar;
		break;
	case 4:
		mSidebar4 = newSideBar;
		break;
	}
	newSideBar->show();
	return true;
}
void SidebarManager::renderSidebars()
{
	if(mSidebar0.get()&&mSidebar0->isFinished())
		mSidebar0.reset();
	if(mSidebar1.get()&&mSidebar1->isFinished())
		mSidebar1.reset();
	if(mSidebar2.get()&&mSidebar2->isFinished())
		mSidebar2.reset();
	if(mSidebar3.get()&&mSidebar3->isFinished())
		mSidebar3.reset();
	if(mSidebar4.get()&&mSidebar4->isFinished())
		mSidebar4.reset();
	
	if(mSidebar0.get())
		mSidebar0->render();
	if(mSidebar1.get())
		mSidebar1->render();
	if(mSidebar2.get())
		mSidebar2->render();
	if(mSidebar3.get())
		mSidebar3->render();
	if(mSidebar4.get())
		mSidebar4->render();
}
