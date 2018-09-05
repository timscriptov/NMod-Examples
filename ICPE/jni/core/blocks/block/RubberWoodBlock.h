#pragma once

#include "blocks/Blocks.h"

class RubberWoodBlock : public IC::Blocks
{
public:
	RubberWoodBlock();
public:
	virtual void tick(BlockSource&, BlockPos const&, Random&)const;
	virtual int getSpawnResourcesAuxValue(unsigned char)const;
	virtual void spawnResources(BlockSource&, BlockPos const&, int, float, int) const;
	virtual int getPlacementDataValue(Entity&, BlockPos const&, signed char, Vec3 const&, int)const;
protected:
	bool canMakeWet(BlockSource&,BlockPos const&)const;
	bool hasLeafAround(BlockSource&,BlockPos const&)const;
	bool hasWoodTop(BlockSource&,BlockPos const&)const;
};
