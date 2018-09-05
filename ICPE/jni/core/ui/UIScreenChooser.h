#pragma once

class ClientInstance;
class BlockSource;
class BlockPos;
class Player;
class MinecraftGame;

class UIScreenChooser
{
private:
	MinecraftGame * game;
public:
	UIScreenChooser(MinecraftGame&);
	UIScreenChooser()=default;
	~UIScreenChooser()=default;
public:
	void pushElectricFurnaceScreen(Player&,BlockPos const&);
	void pushIronFurnaceScreen(Player&,BlockPos const&);
	void pushBatBoxScreen(Player&,BlockPos const&);
	void pushSolarGeneratorScreen(Player&,BlockPos const&);
	void pushFireGeneratorScreen(Player&,BlockPos const&);
	void pushLuminatorScreen(Player&,BlockPos const&);
	void pushMaceratorScreen(Player&,BlockPos const&);
	void pushExtractorScreen(Player&,BlockPos const&);
	void pushCompressorScreen(Player&,BlockPos const&);
};
