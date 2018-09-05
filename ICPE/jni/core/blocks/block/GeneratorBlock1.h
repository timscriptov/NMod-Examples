#pragma once
#if 0
#include <memory>

#include "base/BaseMachineBlock.h"

class GeneratorBlock1 : public BaseMachineBlock
{
public:
	GeneratorBlock1();
public:
	virtual ICBlockEntity* getBlockEntity(BlockSource&,BlockPos const&)const;
	virtual bool isElectricProvider(BlockSource&,BlockPos const&,FacingEnum)const;
	virtual bool isElectricBlock(BlockSource&,BlockPos const&)const;
	virtual std::string buildDescriptionName(unsigned char) const;
	virtual bool hasComparatorSignal()const;
	virtual bool use(Player&, BlockPos const&) const;
	virtual ItemInstance getSilkTouchItemInstance(unsigned char) const;
	virtual int getPlacementDataValue(Entity&, BlockPos const&, signed char, Vec3 const&, int) const;
	virtual int getComparatorSignal(BlockSource&, BlockPos const&, signed char, int)const;
public:
	virtual std::vector<ItemInstance> getSpawnResources(int,Random&)const;
};
#endif
