#include "Sidebar.h"

#include <fstream>

#include "mcpe/client/MinecraftGame.h"
#include "mcpe/client/gui/GuiElement.h"
#include "mcpe/client/gui/GuiData.h"
#include "mcpe/client/gui/IntRectangle.h"
#include "mcpe/client/gui/Font.h"
#include "mcpe/client/renderer/ItemRenderer.h"
#include "mcpe/client/resources/I18n.h"
#include "mcpe/item/ItemInstance.h"
#include "mcpe/util/Color.h"

#define TIME_PERITEM 3000

Sidebar::Sidebar(MinecraftGame&game,int yPosition,int width,int height,std::string const&title,std::string const&summary,ItemInstance const& item)
:mMinecraftGame(game)
{
	mShowingItem = item;
	mXPosition = game.getScreenWidth();
	mYPosition = yPosition;
	mWidth = width;
	mHeight = height;
	mTitleText = I18n::get(title);
	mSummaryText = I18n::get(summary);
	mTimer = TIME_PERITEM;
	mStarted = false;
	mIsShowing = false;
	mIsDismissing = false;
	mFinished = false;
	mShowingProgress = 0;
	mDismissingProgress = 0;
	
	mBackground = std::make_shared<GuiElement>(false,false,0,0,0,0);
	mBackground->xPosition = mXPosition;
	mBackground->yPosition = mYPosition;
	mBackground->width = width;
	mBackground->height = height;
	mBackground->setBackground(&game,"resource_pack/vanilla/textures/gui/greyBorder",IntRectangle{0,0,16,16},4,4);
}
void Sidebar::show()
{
	mStarted = true;
}
void Sidebar::render()
{
	if(mStarted&&!mFinished)
	{
		if(!mIsShowing)
		{
			mIsShowing = true;
		}
		else if(mIsShowing&&!mIsDismissing&&mShowingProgress<mWidth)
		{
			++mShowingProgress;
		}
		else if(mIsShowing&&!mIsDismissing&&mShowingProgress>=mWidth&&mTimer>=0)
		{
			--mTimer;
		}
		else if(mIsShowing&&!mIsDismissing&&mShowingProgress>=mWidth&&mTimer<0)
		{
			mIsDismissing=true;
		}
		else if(mIsShowing&&mIsDismissing&&mDismissingProgress<mWidth)
		{
			++mDismissingProgress;
		}
		else if(mIsShowing&&mIsDismissing&&mDismissingProgress>=mWidth)
		{
			mFinished = true;
		}
		renderUI();
	}
}
void Sidebar::dismiss()
{
	mFinished = true;
}
void Sidebar::renderUI()
{
	int xPosition = 0;
	
	if(mIsShowing&&!mIsDismissing)
		xPosition = mMinecraftGame.getGuiData()->getScreenWidth() - mShowingProgress;
	else if(mIsShowing&&mIsDismissing)
		xPosition = mMinecraftGame.getGuiData()->getScreenWidth() - mWidth + mDismissingProgress;
	mBackground->xPosition = xPosition;
	mBackground->render(&mMinecraftGame,mBackground->xPosition,mBackground->yPosition);
	
	Font* font = mMinecraftGame.getFont();
	font->drawShadow(mTitleText,mBackground->xPosition + mHeight + 4,mBackground->yPosition + 8,Color::WHITE,false,0);
	font->drawShadow(mSummaryText,mBackground->xPosition + mHeight + 4,mBackground->yPosition + 20,Color::WHITE,false,0);
	
	ItemRenderer::instance->renderGuiItemNew(mShowingItem,0,mBackground->xPosition + 14,mBackground->yPosition + 10,1,1,2,false);
}
bool Sidebar::isFinished()
{
	return mFinished;
}
