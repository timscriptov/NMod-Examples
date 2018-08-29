#pragma once

#include "MenuScreen.h"

#include <map>

class TabButton;
class Biome;

class BiomeEditScreen : public MenuScreen
{
private:
	std::shared_ptr<TabButton> mSelectButton;
	std::shared_ptr<TabButton> mPrevButton;
	std::shared_ptr<TabButton> mNextButton;
	std::map<Biome*,std::string> mBiomeData;
	Biome*& mTargetBiome;
public:
	BiomeEditScreen(MinecraftGame&,ClientInstance&,Biome*&);
public:
	virtual void init();
	virtual void setupPositions();
	virtual void render(int,int,float);
	virtual void _buttonClicked(Button&);
private:
	void initBiomeData();
	std::string biomeToString()const;
	void prev();
	void next();
};
