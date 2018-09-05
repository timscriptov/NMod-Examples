#pragma once

#include "ElectricBlock.h"

class ElectricSourceBlock : public ElectricBlock
{
public:
	ElectricSourceBlock(const std::string&, int, const Material&);
public:
	virtual bool isElectricProvider(BlockSource&,BlockPos const&)const;
};
