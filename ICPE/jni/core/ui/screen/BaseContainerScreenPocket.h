#pragma once

#include <memory>
#include <vector>

#include "mcpe/util/BlockPos.h"
#include "mcpe/client/gui/screen/Screen.h"
#include "mcpe/client/gui/IntRectangle.h"
#include "mcpe/client/gui/Font.h"
#include "mcpe/client/gui/GuiElement.h"
#include "mcpe/client/gui/TButton.h"
#include "mcpe/client/renderer/ItemRenderer.h"
#include "mcpe/client/MinecraftGame.h"
#include "mcpe/util/Util.h"
#include "mcpe/item/ItemInstance.h"

class BlockSource;
class Button;
class Label;
class Player;
class GuiElement;
class ItemInstance;
class MovingItemRenderer;

namespace Touch{class TButton;}
namespace Touch{class THeader;}

class BaseContainerScreenPocket : public Screen
{
protected:
	class MovingItemRenderer
	{
	private:
		ItemInstance item;
		float speed;
		float xStart;
		float yStart;
		float xEnd;
		float yEnd;
		float size;
		double renderProgress;
		double lineConstK;
		double lineConstB;
	public:
		MovingItemRenderer()=default;
		MovingItemRenderer(ItemInstance*_item,float xstart,float ystart,float xend,float yend,float speed,float size)
		{
			this->item=*_item;
			this->xStart=xstart;
			this->yStart=ystart;
			this->xEnd=xend;
			this->yEnd=yend;
			this->size=size;
			this->speed=speed;
			this->renderProgress=0;
	
			this->lineConstK=(yEnd-yStart)/(xEnd-xStart);
			this->lineConstB=(yStart*xEnd-yEnd*xStart)/(xEnd-xStart);
		}
		~MovingItemRenderer()=default;
	public:
		void onRender()
		{
			if(finished())return;
	
			renderProgress+=speed;
			float renderXPosition=0;
			if(xEnd<xStart)
				renderXPosition=xStart-(xStart-xEnd)*renderProgress;
			else
				renderXPosition=xStart+(xEnd-xStart)*renderProgress;
			float renderYPosition=lineConstK*renderXPosition+lineConstB;
	
			ItemRenderer::instance->renderGuiItemNew(item,0,renderXPosition+5,renderYPosition+2.5,size,1,1,false);
		}
		bool finished()const
		{
			return renderProgress>=1;
		}
	};
	class ItemPanel
	{
	public:
		ItemInstance item;
		int xPosition;
		int yPosition;
		int selectedCount;
		float selectedProgress;
		int id;
		int width;
		int height;
		bool selected;
	protected:
		std::shared_ptr<GuiElement>background;
	public:
		ItemPanel(int ID,ItemInstance const&i,int x,int y,int w,int h,MinecraftGame&c)
		{
			id=ID;
			item=i;
			xPosition=x;
			yPosition=y;
			selectedCount=-10;
			selectedProgress=0;
			selected=false;
			width=w;
			height=h;
			
			background=std::make_shared<GuiElement>(false,false,0,0,0,0);
			background->xPosition=xPosition;
			background->yPosition=yPosition;
			background->width=width;
			background->height=height;
			background->setBackground(&c,"textures/gui/gui",{229,0,6,6},2,2);
		}
		~ItemPanel()=default;
	public:
		std::shared_ptr<Touch::TButton> getNewButton(MinecraftGame&c)
		{
			std::shared_ptr<Touch::TButton> newBtn=std::make_shared<Touch::TButton>(getTargetButtonID(),"",&c,false,0);
			newBtn->xPosition=xPosition;
			newBtn->yPosition=yPosition;
			newBtn->width=width;
			newBtn->height=height;
			newBtn->setVisible(false);
			return newBtn;
		}
		int getTargetButtonID()const
		{
			return id+1000;
		}
		void render(MinecraftGame&client)
		{
			if(item.count==0)return;
	
			ItemRenderer::instance->renderGuiItemNew(item,0,xPosition+7.5,yPosition+5,10,1,1,false);
			if(selectedCount>=1&&selectedCount<=item.count)
			{
				ScreenRenderer::singletonPtr->fill(xPosition+5,yPosition+3,xPosition+25,yPosition+5,Color(0.4,0.4,0.4,1.0));
				float fprogressInSlot=(float)selectedCount;
				float fItemsCount=(float)item.count;
				float progress=(fprogressInSlot)/(fItemsCount);
				ScreenRenderer::singletonPtr->fill(xPosition+5,yPosition+3,xPosition+5+(20*progress),yPosition+5,Color(0.1,1.0,0.1,1.0));
			}
			if(item.isDamaged())
			{
				ScreenRenderer::singletonPtr->fill(xPosition+5,yPosition+22,xPosition+25,yPosition+23,Color::BLACK);
				float fprogressMaxDamage=(float)item.getMaxDamage();
				float fprogressDamage=(float)fprogressMaxDamage-item.getDamageValue();
				float progress=(fprogressDamage)/(fprogressMaxDamage);
				ScreenRenderer::singletonPtr->fill(xPosition+5,yPosition+22,xPosition+5+(20*progress),yPosition+23,Color(1.0F-1.0F*progress,1.0F*progress,0.1F,1.0F));
			}
			if(item.count>1)
				client.getFont()->drawShadow(item.count>99?"99+":Util::toString(item.count),xPosition+((item.count>9)?15:20),yPosition+20,Color::WHITE,false,0);
		}
		void setSelected(bool b)
		{
			selected=b;
		}
		bool getSelected()const
		{
			return selected;
		}
		std::shared_ptr<GuiElement> getBackground()
		{
			return background;
		}
		int getID()const
		{
			return id;
		}
		ItemInstance getItem()const
		{
			return item;
		}
	};
protected:
	std::string headerName;
	std::shared_ptr<Touch::THeader> header;
	std::shared_ptr<Touch::TButton> buttonClose;
	std::shared_ptr<GuiElement> background;
	std::shared_ptr<GuiElement> closeBackground;
	std::shared_ptr<GuiElement> closeBackground_pressed;
	std::shared_ptr<GuiElement> backgroundSelected;
	std::shared_ptr<GuiElement> itemSlotDarkBackground;
	std::vector<std::shared_ptr<MovingItemRenderer> > movingItems;
	std::vector<std::shared_ptr<ItemPanel> > itemPanels;
	int nowPanelID;
	int progressInSlot[36];
	float itemSelectProgressInSlot[36];
	BlockSource&source;
	Player&player;
public:
	BaseContainerScreenPocket(MinecraftGame&,ClientInstance&,BlockSource&,Player&,std::string const&);
	~BaseContainerScreenPocket()=default;
public:
	virtual std::string getScreenName()const;
	virtual std::string getScreenNameW()const;
	virtual void _buttonClicked(Button&);
	virtual void init();
    virtual bool closeOnPlayerHurt() const;
	virtual void tick();
	virtual void render(int,int,float);
public:
	void drawSlotItemAt(int,int,ItemInstance*);
	void startRenderMovingItem(ItemInstance *,float,float,float,float,float,float);
	void onRenderMovingItem();
	void onSlotMove(float,float,int,float,float,int,unsigned char,bool);
public:
	virtual void onInit();
	virtual void onRender();
	virtual void onItemPanelChanged(ItemPanel&);
	virtual void onRegisterPanels();
	virtual unsigned char getAddItemToItemPanelCount(ItemInstance const&,ItemPanel&);
protected:
	void registerNewItemPanel(int x,int y,int w,int h,ItemInstance const&);
	std::shared_ptr<Button> getButtonByID(int);
	int getItemSlotsStartPos()const;
	static bool isSameItemInstance(ItemInstance const*,ItemInstance const*);
};
