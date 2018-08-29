#pragma once

#include <memory>
#include <string>

#include "mcpe/item/ItemInstance.h"

class MinecraftGame;
class ItemInstance;
class GuiElement;

class Sidebar
{
private:
	MinecraftGame& mMinecraftGame;
	std::shared_ptr<GuiElement> mBackground;
	ItemInstance mShowingItem;
	std::string mTitleText;
	std::string mSummaryText;
	int mWidth;
	int mHeight;
	int mXPosition;
	int mYPosition;
	int mTimer;
	bool mStarted;
	bool mFinished;
	bool mIsShowing;
	bool mIsDismissing;
	int mShowingProgress;
	int mDismissingProgress;
public:
	Sidebar() = delete;
	~Sidebar() = default;
	Sidebar(MinecraftGame&,int yPosition,int width,int height,std::string const&title,std::string const&summary,ItemInstance const& items);
public:
	void show();
	void render();
	void dismiss();
	bool isFinished();
private:
	void renderUI();
};
