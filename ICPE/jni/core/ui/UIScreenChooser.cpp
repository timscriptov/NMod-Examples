#include "UIScreenChooser.h"

#include "mcpe/client/gui/screen/ScreenChooser.h"
#include "mcpe/client/gui/screen/Screen.h"
#include "mcpe/client/settings/Options.h"
#include "mcpe/client/ClientInstance.h"

#include "ui/screen/BatBoxScreenPocket.h"
#include "ui/screen/BatBoxScreenClassic.h"
#include "ui/screen/IronFurnaceScreenPocket.h"
#include "ui/screen/IronFurnaceScreenClassic.h"
#include "ui/screen/SolarGeneratorScreenPocket.h"
#include "ui/screen/SolarGeneratorScreenClassic.h"
#include "ui/screen/FireGeneratorScreenPocket.h"
#include "ui/screen/FireGeneratorScreenClassic.h"
#include "ui/screen/ElectricFurnaceScreenPocket.h"
#include "ui/screen/ElectricFurnaceScreenClassic.h"
#include "ui/screen/LuminatorScreenPocket.h"
#include "ui/screen/LuminatorScreenClassic.h"
#include "ui/screen/MaceratorScreenPocket.h"
#include "ui/screen/MaceratorScreenClassic.h"
#include "ui/screen/ExtractorScreenPocket.h"
#include "ui/screen/ExtractorScreenClassic.h"
#include "ui/screen/CompressorScreenPocket.h"
#include "ui/screen/CompressorScreenClassic.h"

UIScreenChooser::UIScreenChooser(MinecraftGame&g)
{
	game=&g;
}
void UIScreenChooser::pushBatBoxScreen(Player&p,BlockPos const&pos)
{
	if(game->getPrimaryClientInstance()->getOptions()->getUIProfile()==1)
		game->getPrimaryClientInstance()->getScreenChooser()->_pushScreen(std::make_shared<BatBoxScreenPocket>(*game,*game->getPrimaryClientInstance(),p,pos),false);
	else
		game->getPrimaryClientInstance()->getScreenChooser()->_pushScreen(std::make_shared<BatBoxScreenClassic>(*game,*game->getPrimaryClientInstance(),p,pos),false);
}
void UIScreenChooser::pushCompressorScreen(Player&p,BlockPos const&pos)
{
	if(game->getPrimaryClientInstance()->getOptions()->getUIProfile()==1)
		game->getPrimaryClientInstance()->getScreenChooser()->_pushScreen(std::make_shared<CompressorScreenPocket>(*game,*game->getPrimaryClientInstance(),p,pos),false);
	else
		game->getPrimaryClientInstance()->getScreenChooser()->_pushScreen(std::make_shared<CompressorScreenClassic>(*game,*game->getPrimaryClientInstance(),p,pos),false);
}
void UIScreenChooser::pushLuminatorScreen(Player&p,BlockPos const&pos)
{
	if(game->getPrimaryClientInstance()->getOptions()->getUIProfile()==1)
		game->getPrimaryClientInstance()->getScreenChooser()->_pushScreen(std::make_shared<LuminatorScreenPocket>(*game,*game->getPrimaryClientInstance(),p,pos),false);
	else
		game->getPrimaryClientInstance()->getScreenChooser()->_pushScreen(std::make_shared<LuminatorScreenClassic>(*game,*game->getPrimaryClientInstance(),p,pos),false);
}
void UIScreenChooser::pushIronFurnaceScreen(Player&p,BlockPos const&pos)
{
	if(game->getPrimaryClientInstance()->getOptions()->getUIProfile()==1)
		game->getPrimaryClientInstance()->getScreenChooser()->_pushScreen(std::make_shared<IronFurnaceScreenPocket>(*game,*game->getPrimaryClientInstance(),p,pos),false);
	else
		game->getPrimaryClientInstance()->getScreenChooser()->_pushScreen(std::make_shared<IronFurnaceScreenClassic>(*game,*game->getPrimaryClientInstance(),p,pos),false);
}
void UIScreenChooser::pushElectricFurnaceScreen(Player&p,BlockPos const&pos)
{
	if(game->getPrimaryClientInstance()->getOptions()->getUIProfile()==1)
		game->getPrimaryClientInstance()->getScreenChooser()->_pushScreen(std::make_shared<ElectricFurnaceScreenPocket>(*game,*game->getPrimaryClientInstance(),p,pos),false);
	else
		game->getPrimaryClientInstance()->getScreenChooser()->_pushScreen(std::make_shared<ElectricFurnaceScreenClassic>(*game,*game->getPrimaryClientInstance(),p,pos),false);
}
void UIScreenChooser::pushSolarGeneratorScreen(Player&p,BlockPos const&pos)
{
	if(game->getPrimaryClientInstance()->getOptions()->getUIProfile()==1)
		game->getPrimaryClientInstance()->getScreenChooser()->_pushScreen(std::make_shared<SolarGeneratorScreenPocket>(*game,*game->getPrimaryClientInstance(),p,pos),false);
	else
		game->getPrimaryClientInstance()->getScreenChooser()->_pushScreen(std::make_shared<SolarGeneratorScreenClassic>(*game,*game->getPrimaryClientInstance(),p,pos),false);
}
void UIScreenChooser::pushFireGeneratorScreen(Player&p,BlockPos const&pos)
{
	if(game->getPrimaryClientInstance()->getOptions()->getUIProfile()==1)
		game->getPrimaryClientInstance()->getScreenChooser()->_pushScreen(std::make_shared<FireGeneratorScreenPocket>(*game,*game->getPrimaryClientInstance(),p,pos),false);
	else
		game->getPrimaryClientInstance()->getScreenChooser()->_pushScreen(std::make_shared<FireGeneratorScreenClassic>(*game,*game->getPrimaryClientInstance(),p,pos),false);
}
void UIScreenChooser::pushMaceratorScreen(Player&p,BlockPos const&pos)
{
	if(game->getPrimaryClientInstance()->getOptions()->getUIProfile()==1)
		game->getPrimaryClientInstance()->getScreenChooser()->_pushScreen(std::make_shared<MaceratorScreenPocket>(*game,*game->getPrimaryClientInstance(),p,pos),false);
	else
		game->getPrimaryClientInstance()->getScreenChooser()->_pushScreen(std::make_shared<MaceratorScreenClassic>(*game,*game->getPrimaryClientInstance(),p,pos),false);
}
void UIScreenChooser::pushExtractorScreen(Player&p,BlockPos const&pos)
{
	if(game->getPrimaryClientInstance()->getOptions()->getUIProfile()==1)
		game->getPrimaryClientInstance()->getScreenChooser()->_pushScreen(std::make_shared<ExtractorScreenPocket>(*game,*game->getPrimaryClientInstance(),p,pos),false);
	else
		game->getPrimaryClientInstance()->getScreenChooser()->_pushScreen(std::make_shared<ExtractorScreenClassic>(*game,*game->getPrimaryClientInstance(),p,pos),false);
}
