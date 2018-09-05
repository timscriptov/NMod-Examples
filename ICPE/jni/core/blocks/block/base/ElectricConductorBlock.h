#pragma once

#include "ElectricBlock.h"

class ElectricConductorBlock : public ElectricBlock
{
public:
	ElectricConductorBlock(const std::string&, int, const Material&);
public:
	virtual bool isElectricConductor(BlockSource&,BlockPos const&)const;
};
