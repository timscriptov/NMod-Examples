#pragma once

#include <memory>

#include "base/ElectricConductorBlock.h"
#include "blocks/cblockentity/CEntityBlock.h"

class CableBlock : public CEntityBlock
{
public:
	CableBlock();
public:
	virtual std::unique_ptr<CBlockEntity> createBlockEntity(BlockPos const&)const;
	virtual bool isElectricConductor(BlockSource&,BlockPos const&)const;
	virtual AABB const &getVisualShape(BlockSource&, BlockPos const&, AABB&, bool) const;
	virtual AABB const &getVisualShape(unsigned char, AABB&, bool) const;
	virtual void addCollisionShapes(BlockSource&, BlockPos const&, AABB const*, std::vector<AABB, std::allocator<AABB> >&,Entity*) const;
	virtual bool detachesOnPistonMove(BlockSource&, BlockPos const&)const;
	virtual int getResource(Random&, int, int)const;
	virtual int getResourceCount(Random&, int, int)const;
	virtual bool canBeSilkTouched() const;
	virtual int getSpawnResourcesAuxValue(unsigned char)const;
	virtual std::string buildDescriptionName(unsigned char aux) const;
	virtual void neighborChanged(BlockSource&, BlockPos const&, BlockPos const&)const;
	virtual bool entityInside(BlockSource&, BlockPos const&, Entity&)const;
	virtual bool hasComparatorSignal()const;
	virtual int getPlacementDataValue(Entity&, BlockPos const&, signed char, Vec3 const&, int) const;
	virtual int getRenderLayer(BlockSource&, BlockPos const&) const;
	virtual int getComparatorSignal(BlockSource&, BlockPos const&, signed char, int)const;
};
