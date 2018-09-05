#pragma once

#include "mcpe/block/blocks/FenceBlock.h"

class IronFenceBlock : public FenceBlock
{
public:
	IronFenceBlock();
public:
	virtual std::string buildDescriptionName(unsigned char) const;
};
