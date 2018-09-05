#include "BaseContainerScreenClassic.h"

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
#include "mcpe/client/resources/I18n.h"
#include "mcpe/util/Color.h"
#include "mcpe/util/Util.h"
#include "mcpe/entity/player/LocalPlayer.h"
#include "mcpe/entity/player/Inventory.h"
#include "mcpe/inventory/InventoryMenu.h"
#include "mcpe/item/ItemInstance.h"
#include "mcpe/block/Block.h"

BaseContainerScreenClassic::BaseContainerScreenClassic(MinecraftGame&game,ClientInstance&client,BlockSource&s,Player&p,std::string const&name)
:Screen(game,client),source(s),player(p)
{
	headerName=name;
	nowPanelID=0;
	for(int &progress : progressInSlot)
		progress=-10;
	for(float &progress : itemSelectProgressInSlot)
		progress=0;
}
std::string BaseContainerScreenClassic::getScreenName()const
{
	return "base_container_screen_classic";
}
std::string BaseContainerScreenClassic::getScreenNameW()const
{
	return "base_container_screen_classic";
}
void BaseContainerScreenClassic::_buttonClicked(Button&button)
{
	Screen::_buttonClicked(button);
	
	if(&button==closeButton.get())
		mcGame->schedulePopScreen(1);
	else if(button.id>=1000&&nowPanelID!=button.id-1000)
	{
		itemPanels[nowPanelID]->setSelected(false);
		nowPanelID=button.id-1000;
		itemPanels[nowPanelID]->setSelected(true);
	}
}
void BaseContainerScreenClassic::init()
{
	Screen::init();
	
	std::shared_ptr<GuiElement> darkBackground=std::make_shared<GuiElement>(false,false,0,0,0,0);
	darkBackground->xPosition=0;
	darkBackground->yPosition=0;
	darkBackground->width=width;
	darkBackground->height=height;
	darkBackground->setBackground(Color(0.0F,0.0F,0.0F,0.65F));
	tabElementList.push_back(darkBackground);
	
	background=std::make_shared<GuiElement>(false,false,0,0,0,0);
	background->xPosition=width/2-90;
	background->yPosition=height/2-90;
	background->width=180;
	background->height=180;
	background->setBackground(mcGame,"textures/gui/newgui/NormalButtonNoStroke",{0,0,10,10},4,4);
	tabElementList.push_back(background);
	
	closeButton=std::make_shared<Button>(1E4,"",false);
	closeButton->xPosition=width/2+background->width/2-18;
	closeButton->yPosition=height/2-background->height/2+2;
	closeButton->width=16;
	closeButton->height=16;
	closeButton->setVisible(false);
	buttonList.push_back(closeButton);
	
	closeButtonBackground=std::make_shared<GuiElement>(false,false,0,0,0,0);
	closeButtonBackground->xPosition=width/2+background->width/2-18;
	closeButtonBackground->yPosition=height/2-background->height/2+2;
	closeButtonBackground->width=16;
	closeButtonBackground->height=16;
	closeButtonBackground->setBackground(mcGame,"textures/gui/newgui/X",{0,0,16,16},0,0);
	tabElementList.push_back(closeButtonBackground);
	
	int posInInv=0;
	int slotSize=(background->width-8)/9;
	for(int yPos=0;posInInv<36;yPos+=slotSize)
	{
		if(posInInv<9)
			yPos=height/2+slotSize*3+4;
		for(unsigned int xPos=4+width/2-background->width/2;(xPos+slotSize)<(width/2+background->width/2-4)&&posInInv<36;xPos+=slotSize,++posInInv)
		{
			std::shared_ptr<GuiElement> itemSlotBackground=std::make_shared<GuiElement>(false,false,0,0,0,0);
			itemSlotBackground->width=slotSize;
			itemSlotBackground->height=slotSize;
			itemSlotBackground->xPosition=xPos;
			itemSlotBackground->yPosition=yPos;
			itemSlotBackground->setBackground(mcGame,"textures/gui/gui",{188,184,22,22},1,1);
			tabElementList.push_back(itemSlotBackground);
			
			std::shared_ptr<Touch::TButton> newBtn=std::make_shared<Touch::TButton>(posInInv,"",mcGame,false,0);
			newBtn->xPosition=xPos;
			newBtn->yPosition=yPos;
			newBtn->width=slotSize;
			newBtn->height=slotSize;
			newBtn->setVisible(false);
			buttonList.push_back(newBtn);
			
		}
		if(posInInv==9)
			yPos=height/2-slotSize;
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
void BaseContainerScreenClassic::drawSlotItemAt(int x,int y,ItemInstance* item)
{
	if(item)
		ItemRenderer::instance->renderGuiItemNew(*item,0,x+2.5,y,2,1,1,false);
	if(item&&item->count>1)
		mcGame->getFont()->drawShadow(item->count>99?"99+":Util::toString(item->count),x+((item->count>9)?5:10),y+10,Color::WHITE,false,0);
}
void BaseContainerScreenClassic::tick()
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
void BaseContainerScreenClassic::startRenderMovingItem(ItemInstance *item,float xStart,float yStart,float xEnd,float yEnd,float speed,float size)
{
	std::shared_ptr<MovingItemRenderer> newRenderer=std::make_shared<MovingItemRenderer>(item,xStart,yStart,xEnd,yEnd,speed,size);
	movingItems.push_back(newRenderer);
}
void BaseContainerScreenClassic::onRenderMovingItem()
{
	for(std::shared_ptr<MovingItemRenderer>&item : movingItems)
		if(item.get()&&item->finished())
			item.reset();
		else if(item.get())
			item->onRender();
}
void BaseContainerScreenClassic::onSlotMove(float startPosX,float startPosY,int startSlot,float endPosX,float endPosY,int endSlot,unsigned char count,bool isInv)
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
void BaseContainerScreenClassic::render(int i1,int i2,float floatValue)
{
	closeButtonBackground->setBackground(mcGame,closeButton->pressed?"textures/gui/newgui/XPress":"textures/gui/newgui/X",{0,0,16,16},0,0);
	
	for(std::shared_ptr<ItemPanel>& panel : itemPanels)
		if(panel->getSelected())
		{
			backgroundSelected->xPosition=panel->xPosition-3;
			backgroundSelected->yPosition=panel->yPosition-3;
			backgroundSelected->width=panel->width+6;
			backgroundSelected->height=panel->height+6;
		}
	
	Screen::render(i1,i2,floatValue);
	
	int posInInv=0;
	int slotSize=(background->width-8)/9;
	InventoryMenu* invMenu=mcGame->getPrimaryLocalPlayer()->getInventoryMenu();
	
	for(unsigned int yPos=0;posInInv<36;yPos+=slotSize)
	{
		if(posInInv<9)
			yPos=height/2+slotSize*3+4;
		
		for(unsigned int xPos=4+width/2-background->width/2;(xPos+slotSize)<(width/2+background->width/2-4)&&posInInv<36;xPos+=slotSize,++posInInv)
		{
			drawSlotItemAt(xPos,yPos,invMenu->getSlot(posInInv));
			
			if(progressInSlot[posInInv]>=1&&progressInSlot[posInInv]<=invMenu->getSlot(posInInv)->count)
			{
				ScreenRenderer::singletonPtr->fill(xPos+2,yPos+2,xPos+slotSize-2,yPos+4,Color(0.4,0.4,0.4,1.0));
				float fprogressInSlot=(float)progressInSlot[posInInv];
				float fItemsCount=(float)invMenu->getSlot(posInInv)->count;
				float progress=(fprogressInSlot)/(fItemsCount);
				ScreenRenderer::singletonPtr->fill(xPos+2,yPos+2,xPos+2+((slotSize-4)*progress),yPos+4,Color(0.1,1.0,0.1,1.0));
			}
			if(invMenu->getSlot(posInInv)&&invMenu->getSlot(posInInv)->isDamaged())
			{
				ScreenRenderer::singletonPtr->fill(xPos+2,yPos+15,xPos+slotSize-2,yPos+16.5,Color::BLACK);
				float fprogressMaxDamage=(float)invMenu->getSlot(posInInv)->getMaxDamage();
				float fprogressDamage=(float)fprogressMaxDamage-invMenu->getSlot(posInInv)->getDamageValue();
				float progress=(fprogressDamage)/(fprogressMaxDamage);
				ScreenRenderer::singletonPtr->fill(xPos+2,yPos+15,xPos+2+((slotSize-4)*progress),yPos+16.5,Color(1.0F-1.0F*progress,1.0F*progress,0.1F,1.0F));
			}
		}
		if(posInInv==9)
			yPos=height/2-slotSize;
	}
	ScreenRenderer::singletonPtr->drawCenteredString(mcGame->getFont(),I18n::get(headerName),width/2,background->yPosition+2,Color::GREY);
	mcGame->getFont()->drawShadow(I18n::get("container.inventory"),background->xPosition+5,height/2-10,Color::GREY,false,0);
	
	for(std::shared_ptr<ItemPanel>& panel : itemPanels)
		panel->render(*mcGame);
	
	onRender();
	onRenderMovingItem();
}
void BaseContainerScreenClassic::onInit()
{
	
}
void BaseContainerScreenClassic::onRender()
{
	
}
void BaseContainerScreenClassic::onItemPanelChanged(ItemPanel&)
{
	
}
bool BaseContainerScreenClassic::isSameItemInstance(ItemInstance const*i,ItemInstance const*ii)
{
	if(!i->sameItemAndAux(*ii))
		return false;
	if(!i->hasSameUserData(*ii))
		return false;
	return true;
}
unsigned char BaseContainerScreenClassic::getAddItemToItemPanelCount(ItemInstance const&i,ItemPanel&panel)
{
	if(panel.item.isNull())
		return i.getMaxStackSize()<i.count?i.getMaxStackSize():i.count;
	if(!panel.item.sameItemAndAux(i))
		return 0;
	if(panel.item.getMaxStackSize()>i.count)
		return panel.item.getMaxStackSize()-panel.item.count>i.count?i.count:panel.item.getMaxStackSize()-panel.item.count;
	return 0;
}
void BaseContainerScreenClassic::onRegisterPanels()
{
	
}
void BaseContainerScreenClassic::registerNewItemPanel(int x,int y,int w,int h,ItemInstance const&item)
{
	std::shared_ptr<ItemPanel> newPanel=std::make_shared<ItemPanel>(itemPanels.size(),item,x,y,w,h,*mcGame);
	buttonList.push_back(newPanel->getNewButton(*mcGame));
	itemPanels.push_back(newPanel);
	tabElementList.push_back(newPanel->getBackground());
}
std::shared_ptr<Button> BaseContainerScreenClassic::getButtonByID(int id)
{
	for(std::shared_ptr<Button>& btn : buttonList)
		if(btn.get()&&btn->id==id)
			return btn;
}
bool BaseContainerScreenClassic::closeOnPlayerHurt() const
{
	return true;
}
