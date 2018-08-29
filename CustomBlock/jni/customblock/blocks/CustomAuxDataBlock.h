#pragma once

#include "mcpe/block/Block.h"

class CustomAuxDataBlock : public Block
{
public:
	CustomAuxDataBlock(std::string const&,int);
public:
    virtual std::string buildDescriptionName(unsigned char) const;
    virtual bool use(Player&, BlockPos const&)const;
};
