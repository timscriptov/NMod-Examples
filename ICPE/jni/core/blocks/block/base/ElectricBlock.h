#pragma once

#include "blocks/Blocks.h"

class ElectricBlock : public IC::Blocks
{
public:
	ElectricBlock(const std::string&, int, const Material&);
public:
	virtual bool isElectricBlock(BlockSource&,BlockPos const&)const;
};
