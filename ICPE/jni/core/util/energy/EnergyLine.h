#pragma once

#include <vector>

#include "mcpe/util/BlockPos.h"

class EnergyLine
{
public:
	std::vector<BlockPos> line;
public:
	EnergyLine()=default;
	EnergyLine(BlockPos const&);
	~EnergyLine()=default;
public:
	std::vector<BlockPos> toVector()const;
	bool hasPosInList(BlockPos const&);
	EnergyLine clone()const;
	void addNew(BlockPos const&);
	BlockPos getStart()const;
	BlockPos getEnd()const;
};
