#pragma once

#include "Sidebar.h"

#include <memory>

class SidebarManager
{
private:
	std::shared_ptr<Sidebar> mSidebar0;
	std::shared_ptr<Sidebar> mSidebar1;
	std::shared_ptr<Sidebar> mSidebar2;
	std::shared_ptr<Sidebar> mSidebar3;
	std::shared_ptr<Sidebar> mSidebar4;
	MinecraftGame* mMinecraftGame;
public:
	SidebarManager() = default;
	~SidebarManager() = default;
	SidebarManager(MinecraftGame&);
public:
	bool showNewSidebar(std::string const&title,std::string const&summary,ItemInstance const&item);
	void renderSidebars();
};
