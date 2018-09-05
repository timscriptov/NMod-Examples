#include "BaseContainerScreenPocket.h"

#include "mcpe/client/MinecraftGame.h"
#include "mcpe/client/gui/GuiData.h"
#include "mcpe/client/gui/THeader.h"
#include "mcpe/client/gui/TButton.h"
#include "mcpe/client/gui/Label.h"
#include "mcpe/client/gui/GuiElement.h"
#include "mcpe/client/gui/IntRectangle.h"
#include "mcpe/client/gui/Font.h"
#include "mcpe/client/gui/screen/Screen.h"
#include "mcpe/client/gui/screen/ScreenChooser.h"
#include "mcpe/client/renderer/ScreenRenderer.h"
#include "mcpe/client/renderer/ItemRenderer.h"
#include "mcpe/client/settings/Options.h"
#include "mcpe/util/Color.h"
#include "mcpe/util/Util.h"
#include "mcpe/entity/player/LocalPlayer.h"
#include "mcpe/entity/player/Inventory.h"
#include "mcpe/inventory/InventoryMenu.h"
#include "mcpe/item/ItemInstance.h"
#include "mcpe/block/Block.h"

BaseContainerScreenPocket::BaseContainerScreenPocket(MinecraftGame&game,ClientInstance&client,BlockSource&s,Player&p,std::string const&n):Screen(game,client),source(s),player(p)
{
	headerName=n;
	nowPanelID=0;
	for(int &progress : progressInSlot)
		progress=-10;
	for(float &progress : itemSelectProgressInSlot)
		progress=0;
}
void BaseContainerScreenPocket::init()
{
	Screen::init();
	
	int width=mcGame->getGuiData()->getScreenWidth();
	int height=mcGame->getGuiData()->getScreenHeight();
	
	unsigned int posInInv=0;
	for(unsigned int yPos=35;posInInv<36;yPos+=25)
		for(unsigned int xPos=getItemSlotsStartPos();xPos<(width/2-30)&&posInInv<36;xPos+=25)
		{
			std::shared_ptr<Touch::TButton> newBtn=std::make_shared<Touch::TButton>(posInInv++,"",mcGame,false,0);
			newBtn->xPosition=xPos;
			newBtn->yPosition=yPos;
			newBtn->width=25;
			newBtn->height=25;
			newBtn->setVisible(false);
			buttonList.push_back(newBtn);
		}
	int currentID=100;
	
	background=std::make_shared<GuiElement>(false,false,0,0,0,0);
	background->xPosition=0;
	background->yPosition=0;
	background->width=width;
	background->height=height;
	background->setBackground(mcGame,"textures/gui/spritesheet",{34,43,14,14},3,3);
	tabElementList.push_back(background);
	
	header=std::make_shared<Touch::THeader>(++currentID,headerName);
	header->xPosition=0;
	header->yPosition=0;
	header->width=width;
	header->height=25;
	tabElementList.push_back(header);
	
	buttonClose=std::make_shared<Touch::TButton>(++currentID,"",mcGame,false,0);
	buttonClose->xPosition=width-20;
	buttonClose->yPosition=0;
	buttonClose->width=20;
	buttonClose->height=20;
	buttonClose->setVisible(false);
	buttonList.push_back(buttonClose);
	
	closeBackground=std::make_shared<GuiElement>(false,false,0,0,0,0);
	closeBackground->xPosition=width-20;
	closeBackground->yPosition=0;
	closeBackground->width=20;
	closeBackground->height=20;
	closeBackground->setVisible(false);
	closeBackground->setBackground(mcGame,"textures/gui/spritesheet",{60,0,18,18},0,0);
	tabElementList.push_back(closeBackground);
	
	itemSlotDarkBackground=std::make_shared<GuiElement>(false,false,0,0,0,0);
	itemSlotDarkBackground->width=width/2-10;
	itemSlotDarkBackground->height=height-35;
	itemSlotDarkBackground->xPosition=5;
	itemSlotDarkBackground->yPosition=30;
	itemSlotDarkBackground->setBackground(Color(0.25,0.25,0.25,1.0));
	tabElementList.push_back(itemSlotDarkBackground);


	posInInv=0;
	for(unsigned int yPos=35;posInInv<36;yPos+=25)
		for(unsigned int xPos=getItemSlotsStartPos();xPos<(width/2-30)&&posInInv<36;xPos+=25,++posInInv)
		{
			std::shared_ptr<GuiElement> itemSlotBackground=std::make_shared<GuiElement>(false,false,0,0,0,0);
			itemSlotBackground->width=25;
			itemSlotBackground->height=25;
			itemSlotBackground->xPosition=xPos;
			itemSlotBackground->yPosition=yPos;
			itemSlotBackground->setBackground(mcGame,"textures/gui/gui",{200,46,16,16},2,2);
			tabElementList.push_back(itemSlotBackground);
		}
	onRegisterPanels();
	if(itemPanels.size()>0)
		itemPanels[0]->setSelected(true);
	
	backgroundSelected=std::make_shared<GuiElement>(false,false,0,0,0,0);
	backgroundSelected->xPosition=-50;
	backgroundSelected->yPosition=-50;
	backgroundSelected->width=0;
	backgroundSelected->height=0;
	backgroundSelected->setBackground(mcGame,"textures/gui/gui",{0,22,24,24},3,3);
	tabElementList.push_back(backgroundSelected);
	onInit();
}
void BaseContainerScreenPocket::tick()
{
	Screen::tick();
	InventoryMenu* invMenu=mcGame->getPrimaryLocalPlayer()->getInventoryMenu();
	
	for(std::shared_ptr<Button>& btn : buttonList)
	{
		//inv
		
		if(btn.get()&&btn->id<36&&invMenu->getSlot(btn->id)&&btn->msg==""&&btn->pressed)
		{
			if(progressInSlot[btn->id]<1)
				++progressInSlot[btn->id];
			else if(progressInSlot[btn->id]>=1&&progressInSlot[btn->id]<invMenu->getSlot(btn->id)->count)
			{
				float itemProgress=invMenu->getSlot(btn->id)->count;
				if(itemSelectProgressInSlot[btn->id]<1)
					itemSelectProgressInSlot[btn->id]+=((float)itemProgress/64.0F);
				else if(itemSelectProgressInSlot[btn->id]>=1)
					++progressInSlot[btn->id],itemSelectProgressInSlot[btn->id]=0;
			}
			else if(progressInSlot[btn->id]==invMenu->getSlot(btn->id)->count)
				onSlotMove(btn->xPosition,btn->yPosition,btn->id,itemPanels[nowPanelID]->xPosition,itemPanels[nowPanelID]->yPosition,nowPanelID,progressInSlot[btn->id],true),progressInSlot[btn->id]=-10;
		}
		else if(btn.get()&&btn->id<36&&invMenu->getSlot(btn->id)&&btn->msg==""&&!btn->pressed)
		{
			if(progressInSlot[btn->id]>-10&&progressInSlot[btn->id]<2)
				onSlotMove(btn->xPosition,btn->yPosition,btn->id,itemPanels[nowPanelID]->xPosition,itemPanels[nowPanelID]->yPosition,nowPanelID,1,true),progressInSlot[btn->id]=-10;
			else if(progressInSlot[btn->id]>1&&progressInSlot[btn->id]<invMenu->getSlot(btn->id)->count)
				onSlotMove(btn->xPosition,btn->yPosition,btn->id,itemPanels[nowPanelID]->xPosition,itemPanels[nowPanelID]->yPosition,nowPanelID,progressInSlot[btn->id],true),progressInSlot[btn->id]=-10;
		}
		//panels
		
		if(btn.get()&&btn->id>=1000&&btn->id-1000==nowPanelID&&itemPanels[btn->id-1000]->item.count>0&&btn->msg==""&&btn->pressed)
		{
			if(itemPanels[btn->id-1000]->selectedCount<1)
				++itemPanels[btn->id-1000]->selectedCount;
			else if(itemPanels[btn->id-1000]->selectedCount>=1&&itemPanels[btn->id-1000]->selectedCount<itemPanels[btn->id-1000]->item.count)
			{
				float itemProgress=itemPanels[btn->id-1000]->item.count;
				if(itemPanels[btn->id-1000]->selectedProgress<1)
					itemPanels[btn->id-1000]->selectedProgress+=((float)itemProgress/64.0F);
				else if(itemPanels[btn->id-1000]->selectedProgress>=1)
					++itemPanels[btn->id-1000]->selectedCount,itemPanels[btn->id-1000]->selectedProgress=0;
			}
			else if(itemPanels[btn->id-1000]->selectedCount==itemPanels[btn->id-1000]->item.count)
				onSlotMove(btn->xPosition,btn->yPosition,btn->id-1000,0,0,0,itemPanels[btn->id-1000]->selectedCount,false),itemPanels[btn->id-1000]->selectedCount=-10;
		}
		else if(btn.get()&&btn->id>=1000&&btn->id-1000==nowPanelID&&itemPanels[btn->id-1000]->item.count>0&btn->msg==""&&!btn->pressed)
		{
			if(itemPanels[btn->id-1000]->selectedCount>-10&&itemPanels[btn->id-1000]->selectedCount<2)
				onSlotMove(btn->xPosition,btn->yPosition,btn->id-1000,0,0,0,1,false),itemPanels[btn->id-1000]->selectedCount=-10;
			else if(itemPanels[btn->id-1000]->selectedCount>1&&itemPanels[btn->id-1000]->selectedCount<itemPanels[btn->id-1000]->item.count)
				onSlotMove(btn->xPosition,btn->yPosition,btn->id-1000,0,0,0,itemPanels[btn->id-1000]->selectedCount,false),itemPanels[btn->id-1000]->selectedCount=-10;
		}
	}
}
void BaseContainerScreenPocket::render(int int1,int int2,float floatvalue)
{
	InventoryMenu* invMenu=mcGame->getPrimaryLocalPlayer()->getInventoryMenu();
	closeBackground->setBackground(mcGame,"textures/gui/spritesheet",{buttonClose->pressed?78:60,0,18,18},0,0);
	
	for(std::shared_ptr<ItemPanel>& panel : itemPanels)
		if(panel->getSelected())
		{
			backgroundSelected->xPosition=panel->xPosition-3;
			backgroundSelected->yPosition=panel->yPosition-3;
			backgroundSelected->width=panel->width+6;
			backgroundSelected->height=panel->height+6;
		}
	
	//render background
	Screen::render(int1,int2,floatvalue);

	//render inventory items
	unsigned int posInInv=0;
	for(unsigned int yPos=35;posInInv<36;yPos+=25)
	{
		for(unsigned int xPos=getItemSlotsStartPos();xPos<(width/2-30)&&posInInv<36;xPos+=25)
		{
			drawSlotItemAt(xPos,yPos,invMenu->getSlot(posInInv++));
			if(progressInSlot[posInInv-1]>=1&&progressInSlot[posInInv-1]<=invMenu->getSlot(posInInv-1)->count)
			{
				ScreenRenderer::singletonPtr->fill(xPos+5,yPos+3,xPos+20,yPos+5,Color(0.4,0.4,0.4,1.0));
				float fprogressInSlot=(float)progressInSlot[posInInv-1];
				float fItemsCount=(float)invMenu->getSlot(posInInv-1)->count;
				float progress=(fprogressInSlot)/(fItemsCount);
				ScreenRenderer::singletonPtr->fill(xPos+5,yPos+3,xPos+5+(15*progress),yPos+5,Color(0.1,1.0,0.1,1.0));
			}
			if(invMenu->getSlot(posInInv-1)&&invMenu->getSlot(posInInv-1)->isDamaged())
			{
				ScreenRenderer::singletonPtr->fill(xPos+5,yPos+19,xPos+20,yPos+20,Color::BLACK);
				float fprogressMaxDamage=(float)invMenu->getSlot(posInInv-1)->getMaxDamage();
				float fprogressDamage=(float)fprogressMaxDamage-invMenu->getSlot(posInInv-1)->getDamageValue();
				float progress=(fprogressDamage)/(fprogressMaxDamage);
				ScreenRenderer::singletonPtr->fill(xPos+5,yPos+19,xPos+5+(15*progress),yPos+20,Color(1.0F-1.0F*progress,1.0F*progress,0.1F,1.0F));
			}
		}
	}
	//render panels
	for(std::shared_ptr<ItemPanel>& panel : itemPanels)
		panel->render(*mcGame);
	
	onRender();
	onRenderMovingItem();
}
std::string BaseContainerScreenPocket::getScreenName()const
{
	return "base_container_screen_pocket";
}
std::string BaseContainerScreenPocket::getScreenNameW()const
{
	return "base_container_screen_pocket";
}
void BaseContainerScreenPocket::_buttonClicked(Button&btn)
{
	if(buttonClose.get()==&btn)
		mcGame->getScreenChooser()->schedulePopScreen(1);
	if(btn.id>=1000&&nowPanelID!=btn.id-1000)
	{
		itemPanels[nowPanelID]->setSelected(false);
		nowPanelID=btn.id-1000;
		itemPanels[nowPanelID]->setSelected(true);
	}
}
void BaseContainerScreenPocket::drawSlotItemAt(int x,int y,ItemInstance* item)
{
	if(item)
		ItemRenderer::instance->renderGuiItemNew(*item,0,x+5,y+2.5,2,1,1,false);
	if(item&&item->count>1)
		mcGame->getFont()->drawShadow(item->count>99?"99+":Util::toString(item->count),x+((item->count>9)?10:15),y+15,Color::WHITE,false,0);
}
void BaseContainerScreenPocket::startRenderMovingItem(ItemInstance *item,float xStart,float yStart,float xEnd,float yEnd,float speed,float size)
{
	std::shared_ptr<MovingItemRenderer> newRenderer=std::make_shared<MovingItemRenderer>(item,xStart,yStart,xEnd,yEnd,speed,size);
	movingItems.push_back(newRenderer);
}
void BaseContainerScreenPocket::onRenderMovingItem()
{
	for(std::shared_ptr<MovingItemRenderer>&item : movingItems)
		if(item.get()&&item->finished())
			item.reset();
		else if(item.get())
			item->onRender();
}
void BaseContainerScreenPocket::onInit()
{
	
}
void BaseContainerScreenPocket::onRender()
{
	
}
void BaseContainerScreenPocket::onSlotMove(float startPosX,float startPosY,int startSlot,float endPosX,float endPosY,int endSlot,unsigned char count,bool isInv)
{
	if(count<1)return;
	if(itemPanels.size()<1)return;
	
	if(isInv)
	{
		InventoryMenu* invMenu=mcGame->getPrimaryLocalPlayer()->getInventoryMenu();
		ItemInstance* item=invMenu->getSlot(startSlot);
		if(!item||item->isNull())
			return;
		ItemInstance copyItem=item->clone();
		copyItem.count=count;
		ItemInstance addItem=item->clone();
		addItem.count=count;
		
		if(getAddItemToItemPanelCount(addItem,*itemPanels[endSlot].get())>0)
		{
			item->remove((int)getAddItemToItemPanelCount(addItem,*itemPanels[endSlot].get()));
			addItem.count=getAddItemToItemPanelCount(addItem,*itemPanels[endSlot].get())+itemPanels[endSlot]->item.count;
			itemPanels[endSlot]->item=addItem;
			startRenderMovingItem(&copyItem,startPosX,startPosY,endPosX,endPosY,0.05,1.5);
		}
		onItemPanelChanged(*itemPanels[endSlot].get());
	}
	else
	{
		if(itemPanels[startSlot]->item.count==0)
			return;
		ItemInstance* item=&itemPanels[startSlot]->item;
		ItemInstance copyItem;
		copyItem=itemPanels[startSlot]->item.clone();
		copyItem.count=count;
		InventoryMenu* invMenu=mcGame->getPrimaryLocalPlayer()->getInventoryMenu();
		ItemInstance *itemsInv[36];
		int itemsLeft=count;
		for(unsigned char pos=0;pos<36;++pos)
			itemsInv[pos]=invMenu->getSlot(pos);
		for(unsigned char pos=0;pos<36&&itemsLeft>0;++pos)
		{
			if(itemsInv[pos]&&!itemsInv[pos]->isNull()&&isSameItemInstance(itemsInv[pos],&copyItem))
			{
				if(itemsInv[pos]->count<copyItem.getMaxStackSize())
				{
					itemsLeft-=copyItem.getMaxStackSize()-itemsInv[pos]->count;
					startRenderMovingItem(&copyItem,startPosX,startPosY,getButtonByID(pos)->xPosition,getButtonByID(pos)->yPosition,0.05,1.5);
				}
			}
		}
		for(unsigned char pos=0;pos<36&&itemsLeft>0;++pos)
		{
			if(!itemsInv[pos])
			{
				itemsLeft-=copyItem.getMaxStackSize()>itemsLeft?itemsLeft:copyItem.getMaxStackSize();
				startRenderMovingItem(&copyItem,startPosX,startPosY,getButtonByID(pos)->xPosition,getButtonByID(pos)->yPosition,0.05,1.5);
			}
		}
		item->count-=count;
		if(item->count==0)item->setNull();
		ItemInstance item_=copyItem;
		item_.count=count;
		player.add(item_);
		if(!item_.isNull())
			player.drop(item_,false);
		onItemPanelChanged(*itemPanels[startSlot].get());
	}
}
void BaseContainerScreenPocket::onItemPanelChanged(ItemPanel&)
{
	
}
bool BaseContainerScreenPocket::isSameItemInstance(ItemInstance const*i,ItemInstance const*ii)
{
	if(!i->sameItemAndAux(*ii))
		return false;
	if(!i->hasSameUserData(*ii))
		return false;
	return true;
}
unsigned char BaseContainerScreenPocket::getAddItemToItemPanelCount(ItemInstance const&i,ItemPanel&panel)
{
	if(panel.item.isNull())
		return i.getMaxStackSize()<i.count?i.getMaxStackSize():i.count;
	if(!panel.item.sameItemAndAux(i))
		return 0;
	if(panel.item.getMaxStackSize()>i.count)
		return panel.item.getMaxStackSize()-panel.item.count>i.count?i.count:panel.item.getMaxStackSize()-panel.item.count;
	return 0;
}
void BaseContainerScreenPocket::onRegisterPanels()
{
	
}
void BaseContainerScreenPocket::registerNewItemPanel(int x,int y,int w,int h,ItemInstance const&item)
{
	std::shared_ptr<ItemPanel> newPanel=std::make_shared<ItemPanel>(itemPanels.size(),item,x,y,w,h,*mcGame);
	buttonList.push_back(newPanel->getNewButton(*mcGame));
	itemPanels.push_back(newPanel);
	tabElementList.push_back(newPanel->getBackground());
}
std::shared_ptr<Button> BaseContainerScreenPocket::getButtonByID(int id)
{
	for(std::shared_ptr<Button>& btn : buttonList)
		if(btn.get()&&btn->id==id)
			return btn;
}
int BaseContainerScreenPocket::getItemSlotsStartPos()const
{
	int left = ((width/2-30)%25)/2;
	return left+15;
}
bool BaseContainerScreenPocket::closeOnPlayerHurt() const
{
	return true;
}
