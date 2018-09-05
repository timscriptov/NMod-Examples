#include "ProgressController.h"

#include "mcpe/client/gui/IntRectangle.h"

void ProgressController::setMacerate(MinecraftGame&c,int x,int y,int w,int h,float p,std::shared_ptr<GuiElement>ele,bool empty)
{
	setProgress(p);
	int const textureW=21;
	int const textureH=11;
	if(w<textureW&&h<textureH)
		return;
	int const standardW=w-w%textureW;
	int const standardH=h-h%textureH;
	int const startX=(w%textureW)/2+x;
	int const startY=(h%textureH)/2+y;
	
	if(empty)
	{
		ele->setBackground(&c,"images/icpeui/common",{165,32,textureW,textureH},0,0);
		ele->xPosition=startX;
		ele->yPosition=startY;
		ele->width=standardW;
		ele->height=standardH;
	}
	else
	{
		ele->setBackground(&c,"images/icpeui/common",{165,48,textureW*p,textureH},0,0);
		ele->xPosition=startX;
		ele->yPosition=startY;
		ele->width=standardW*p;
		ele->height=standardH;
	}
}
void ProgressController::setExtracte(MinecraftGame&c,int x,int y,int w,int h,float p,std::shared_ptr<GuiElement>ele,bool empty)
{
	setProgress(p);
	int const textureW=22;
	int const textureH=16;
	if(w<textureW&&h<textureH)
		return;
	int const standardW=w-w%textureW;
	int const standardH=h-h%textureH;
	int const startX=(w%textureW)/2+x;
	int const startY=(h%textureH)/2+y;
	
	if(empty)
	{
		ele->setBackground(&c,"images/icpeui/common",{165,96,textureW,textureH},0,0);
		ele->xPosition=startX;
		ele->yPosition=startY;
		ele->width=standardW;
		ele->height=standardH;
	}
	else
	{
		ele->setBackground(&c,"images/icpeui/common",{165,112,textureW*p,textureH},0,0);
		ele->xPosition=startX;
		ele->yPosition=startY;
		ele->width=standardW*p;
		ele->height=standardH;
	}
}
void ProgressController::setCompress(MinecraftGame&c,int x,int y,int w,int h,float p,std::shared_ptr<GuiElement>ele,bool empty)
{
	setProgress(p);
	int const textureW=22;
	int const textureH=16;
	if(w<textureW&&h<textureH)
		return;
	int const standardW=w-w%textureW;
	int const standardH=h-h%textureH;
	int const startX=(w%textureW)/2+x;
	int const startY=(h%textureH)/2+y;
	
	if(empty)
	{
		ele->setBackground(&c,"images/icpeui/common",{165,64,textureW,textureH},0,0);
		ele->xPosition=startX;
		ele->yPosition=startY;
		ele->width=standardW;
		ele->height=standardH;
	}
	else
	{
		ele->setBackground(&c,"images/icpeui/common",{165,80,textureW*p,textureH},0,0);
		ele->xPosition=startX;
		ele->yPosition=startY;
		ele->width=standardW*p;
		ele->height=standardH;
	}
}
void ProgressController::setProcess(MinecraftGame&c,int x,int y,int w,int h,float p,std::shared_ptr<GuiElement>ele,bool empty)
{
	setProgress(p);
	int const textureW=22;
	int const textureH=15;
	if(w<textureW&&h<textureH)
		return;
	int const standardW=w-w%textureW;
	int const standardH=h-h%textureH;
	int const startX=(w%textureW)/2+x;
	int const startY=(h%textureH)/2+y;
	
	if(empty)
	{
		ele->setBackground(&c,"textures/gui/spritesheet",{73,20,textureW,textureH},0,0);
		ele->xPosition=startX;
		ele->yPosition=startY;
		ele->width=standardW;
		ele->height=standardH;
	}
	else
	{
		ele->setBackground(&c,"textures/gui/spritesheet",{73,36,textureW*p,textureH},0,0);
		ele->xPosition=startX;
		ele->yPosition=startY;
		ele->width=standardW*p;
		ele->height=standardH;
	}
}
void ProgressController::setEnergySmall(MinecraftGame&c,int x,int y,int w,int h,float p,std::shared_ptr<GuiElement>ele,bool empty)
{
	setProgress(p);
	int const textureW=16;
	int const textureH=16;
	if(w<textureW&&h<textureH)
		return;
	int const standardW=w-w%textureW;
	int const standardH=h-h%textureH;
	int const startX=(w%textureW)/2+x;
	int const startY=(h%textureH)/2+y;
	
	if(empty)
	{
		ele->setBackground(&c,"images/icpeui/common",{96,64,textureW,textureH},0,0);
		ele->xPosition=startX;
		ele->yPosition=startY;
		ele->width=standardW;
		ele->height=standardH;
	}
	else
	{
		ele->setBackground(&c,"images/icpeui/common",{112,64+textureH-textureH*p,textureW,textureH*p},0,0);
		ele->xPosition=startX;
		ele->yPosition=startY+(standardH-standardH*p);
		ele->width=standardW;
		ele->height=standardH*p;
	}
}
void ProgressController::setFire(MinecraftGame&c,int x,int y,int w,int h,float p,std::shared_ptr<GuiElement>ele,bool empty)
{
	setProgress(p);
	int const textureW=16;
	int const textureH=16;
	if(w<textureW&&h<textureH)
		return;
	int const standardW=w-w%textureW;
	int const standardH=h-h%textureH;
	int const startX=(w%textureW)/2+x;
	int const startY=(h%textureH)/2+y;
	
	if(empty)
	{
		ele->setBackground(&c,"textures/gui/spritesheet",{40,20,textureW,textureH},0,0);
		ele->xPosition=startX;
		ele->yPosition=startY;
		ele->width=standardW;
		ele->height=standardH;
	}
	else
	{
		ele->setBackground(&c,"textures/gui/spritesheet",{56,20+textureH-textureH*p,textureW,textureH*p},0,0);
		ele->xPosition=startX;
		ele->yPosition=startY+(standardH-standardH*p);
		ele->width=standardW;
		ele->height=standardH*p;
	}
}
void ProgressController::setEnergyLarge(MinecraftGame&c,int x,int y,int w,int h,float p,std::shared_ptr<GuiElement>ele,bool empty)
{
	setProgress(p);
	int const textureW=32;
	int const textureH=17;
	if(w<textureW&&h<textureH)
		return;
	int const standardW=w-w%textureW;
	int const standardH=h-h%textureH;
	int const startX=(w%textureW)/2+x;
	int const startY=(h%textureH)/2+y;
	
	if(empty)
	{
		ele->setBackground(&c,"images/icpeui/common",{128,7,textureW,textureH},0,0);
		ele->xPosition=startX;
		ele->yPosition=startY;
		ele->width=standardW;
		ele->height=standardH;
	}
	else
	{
		ele->setBackground(&c,"images/icpeui/common",{128,39,textureW*p,textureH},0,0);
		ele->xPosition=startX;
		ele->yPosition=startY;
		ele->width=standardW*p;
		ele->height=standardH;
	}
}
void ProgressController::setProgress(float&f)
{
	if(f>=1)
		f=1;
	else if(f<=0)
		f=0;
}
