#pragma once
#if 0
#include "blocks/cblockentity/CEntityBlock.h"

class LuminatorActiveBlock : public CEntityBlock
{
public:
	LuminatorActiveBlock();
public:
	virtual bool isElectricBlock(BlockSource&,BlockPos const&)const;
	virtual bool isElectricReceiver(BlockSource&,BlockPos const&,FacingEnum)const;
	virtual ICBlockEntity* getBlockEntity(BlockSource&,BlockPos const&)const;
	virtual bool use(Player&, BlockPos const&)const;
	virtual int getPlacementDataValue(Entity&, BlockPos const&, signed char, Vec3 const&, int) const;
	virtual const AABB& getVisualShape(BlockSource&, BlockPos const&, AABB&, bool) const;
	virtual const AABB& getVisualShape(unsigned char, AABB&, bool) const;
};
#endif
