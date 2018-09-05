#pragma once

#include "mcpe/util/FullBlock.h"

#include "mcpe/level/gen/Feature.h"

class FullBlock;
class BlockPos;
class BlockSource;
class Random;

namespace IC
{
class FallenRubTreeFeature : public Feature
{
protected:
	FullBlock log;
public:
	FallenRubTreeFeature(FullBlock const&log);
	~FallenRubTreeFeature()=default;
public:
	bool place(BlockSource&,BlockPos const&,Random&)const;
protected:
	bool canBeReplacedByLeaves(BlockSource&,BlockPos const&)const;
	bool canBeReplacedByWood(BlockSource&,BlockPos const&)const;
	bool placeFallen(BlockSource&,BlockPos const&,Random&)const;
};
}
