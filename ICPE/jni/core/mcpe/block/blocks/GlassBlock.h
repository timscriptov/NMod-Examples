#pragma once

#include "../Block.h"

class GlassBlock : public Block
{
public:
	bool boolInGlassBlock;
public:
	//virtual bool canProvideSupport(BlockSource&, BlockPos const&, signed char, BlockSupportType) const;
	virtual int getResourceCount(Random&, int, int) const;
	virtual void asItemInstance(BlockSource&, BlockPos const&, int) const;
	virtual std::string buildDescriptionName(unsigned char) const;
	virtual ItemInstance getSilkTouchItemInstance(unsigned char) const;
public:
	GlassBlock(std::string const&, int, Material const&, bool);
};
