#pragma once

#include <vector>
#include "mcpe/util/BlockPos.h"
#include "EnergyLine.h"
#include "util/FacingEnum.h"

class BlockSource;

class EnergySpreader
{
private:
	std::vector<EnergyLine> lines;
	BlockSource&s;
	BlockPos const pos;
public:
	EnergySpreader(BlockSource&,BlockPos const&);
	~EnergySpreader()=default;
public:
	void calculate();
	bool isReceiver(FacingEnum,BlockPos const&);
	bool isConductor(BlockPos const&,BlockPos const&);
	bool isConductor(BlockPos const&);
	bool isProvider(FacingEnum,BlockPos const&);
	void _calculate(BlockPos const&,EnergyLine);
	void addAndCalculate(BlockPos const&,EnergyLine);
	void newEnergyLine(EnergyLine,BlockPos const&);
	std::vector<EnergyLine> getEnergyLines()const;
};
