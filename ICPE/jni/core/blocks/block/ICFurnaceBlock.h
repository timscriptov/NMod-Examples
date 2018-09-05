#pragma once

#if 0
#include "base/BaseMachineBlock.h"

class ICFurnaceBlock : public BaseMachineBlock
{
public:
	ICFurnaceBlock();
public:
	virtual std::string buildDescriptionName(unsigned char) const;
	virtual bool isElectricBlock(BlockSource&,BlockPos const&)const;
	virtual bool isElectricReceiver(BlockSource&,BlockPos const&,FacingEnum)const;
	virtual ICBlockEntity* getBlockEntity(BlockSource&,BlockPos const&)const;
	virtual bool use(Player&, BlockPos const&)const;
public:
	virtual std::vector<ItemInstance> getSpawnResources(int,Random&)const;
	virtual int getPlacementDataValue(Entity&, BlockPos const&, signed char, Vec3 const&, int)const;
};
#endif
