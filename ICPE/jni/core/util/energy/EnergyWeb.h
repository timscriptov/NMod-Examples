#pragma once

#include <vector>

#include "mcpe/util/BlockPos.h"

#include "EnergyLine.h"
#include "Energy.h"

class BlockSource;

class EnergyWeb
{
private:
	BlockPos startPos;
	BlockSource*ps;
	std::vector<EnergyLine> energyLines;
public:
	EnergyWeb(BlockSource&,BlockPos const&);
	~EnergyWeb()=default;
	EnergyWeb();
public:
	std::vector<EnergyLine> getEnergyLines()const;
	void spreadEnergy(Energy&,unsigned long long);
	BlockPos getStartPos()const;
	void setStartPos(BlockPos const&);
};
