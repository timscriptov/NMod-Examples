#pragma once

#include "mcpe/client/gui/GuiElement.h"
#include <memory>

class MinecraftGame;

class ProgressController
{
public:
	static void setCompress(MinecraftGame&,int,int,int,int,float,std::shared_ptr<GuiElement>,bool);
	static void setProcess(MinecraftGame&,int,int,int,int,float,std::shared_ptr<GuiElement>,bool);
	static void setEnergySmall(MinecraftGame&,int,int,int,int,float,std::shared_ptr<GuiElement>,bool);
	static void setEnergyLarge(MinecraftGame&,int,int,int,int,float,std::shared_ptr<GuiElement>,bool);
	static void setFire(MinecraftGame&,int,int,int,int,float,std::shared_ptr<GuiElement>,bool);
	static void setMacerate(MinecraftGame&,int,int,int,int,float,std::shared_ptr<GuiElement>,bool);
	static void setExtracte(MinecraftGame&,int,int,int,int,float,std::shared_ptr<GuiElement>,bool);
private:
	static void setProgress(float&);
};
