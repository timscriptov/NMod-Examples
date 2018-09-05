#pragma once

#include "blocks/cblockentity/CEntityBlock.h"

class BaseMachineBlock : public CEntityBlock
{
public:
	BaseMachineBlock(const std::string&, int, const Material&);
public:
	virtual bool use(Player&, BlockPos const&) const;
	virtual bool isAnyAuxValueInRecipe()const;
	virtual int getResource(Random&, int, int)const;
	virtual int getResourceCount(Random&, int, int)const;
	virtual bool canBeSilkTouched() const;
	virtual int getSpawnResourcesAuxValue(unsigned char)const;
	virtual void spawnResources(BlockSource&, BlockPos const&, int, float, int) const;
public:
	virtual std::vector<ItemInstance> getSpawnResources(int,Random&)const;
	virtual bool isMachineBlock(BlockSource&,BlockPos const&)const;
};
