#pragma once

#include "blocks/Blocks.h"

class ResinBlock : public IC::Blocks
{
public:
	ResinBlock();
public:
	virtual std::string buildDescriptionName(unsigned char) const;
	virtual void onFallOn(BlockSource&, BlockPos const&, Entity*, float) const;
	virtual void onStepOn(Entity&, BlockPos const&) const;
	virtual int getSpawnResourcesAuxValue(unsigned char)const;
	virtual bool mayPlaceOn(Block const&)const;
	virtual void onPlace(BlockSource&, BlockPos const&) const;
	virtual void neighborChanged(BlockSource&, BlockPos const&, BlockPos const&)const;
};
