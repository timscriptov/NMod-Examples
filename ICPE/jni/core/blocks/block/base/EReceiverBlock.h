#pragma once

#include "ElectricBlock.h"

class EReceiverBlock : public ElectricBlock
{
public:
	EReceiverBlock(const std::string&, int, const Material&);
public:
	virtual bool isElectricReceiver(BlockSource&,BlockPos const&)const;
};
