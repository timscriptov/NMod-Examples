#pragma once

#include "mcpe/block/blocks/TntBlock.h"

class ITNTBlock : public TntBlock
{
public:
	ITNTBlock();
public:
	virtual std::string buildDescriptionName(unsigned char) const;
};
