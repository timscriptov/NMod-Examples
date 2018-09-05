#include "LuminatorActiveBlock.h"
#if 0
#include "ICPE.h"
#include "ui/UIScreenChooser.h"

#include "mcpe/item/ItemInstance.h"
#include "mcpe/entity/player/Player.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/client/resources/I18n.h"
#include "blocks/blockentity/LuminatorBlockEntity.h"

LuminatorActiveBlock::LuminatorActiveBlock():ICEntityBlock("te.luminator_flat",IC::Blocks::ID::mLuminatorActive,Material::getMaterial(MaterialType::LAMP))
{
	init();
	setCategory(CreativeItemCategory::DECORATIONS);
	setSolid(false);
	setDestroyTime(2);
	setExplodeable(10);
	setLightEmission(1.0F);
}
bool LuminatorActiveBlock::use(Player&p, BlockPos const&pos)const
{
	ICPE::mUIScreenChooser.pushLuminatorScreen(p,pos);
	return true;
}
ICBlockEntity* LuminatorActiveBlock::getBlockEntity(BlockSource&s,BlockPos const&pos)const
{
	return new LuminatorBlockEntity(s,pos,this);
}
bool LuminatorActiveBlock::isElectricBlock(BlockSource&s,BlockPos const&pos)const
{
	return true;
}
bool LuminatorActiveBlock::isElectricReceiver(BlockSource&s,BlockPos const&pos,FacingEnum)const
{
	return true;
}
const AABB &LuminatorActiveBlock::getVisualShape(BlockSource&source, BlockPos const&pos, AABB&, bool) const
{
	switch(source.getData(pos)-1)
	{
	case 1:
		return AABB(0,0,0,1,0.0625,1);
		break;
	case 0:
		if(source.getBlock(BlockPos(pos.x,pos.y+1,pos.z))==mBlocks[ID::mCable])
			return AABB(0,0.9375,0,1,1,1);
		return AABB(0.125,0.9375,0.125,0.875,1,0.875);
		break;
	case 3:
		if(source.getBlock(BlockPos(pos.x,pos.y,pos.z-1))==mBlocks[ID::mCable])
			return AABB(0,0,0,1,1,0.0625);
		return AABB(0,0.125,0,1,0.875,0.0625);
		break;
	case 2:
		if(source.getBlock(BlockPos(pos.x,pos.y,pos.z+1))==mBlocks[ID::mCable])
			return AABB(0,0,0.9375,1,1,1);
		return AABB(0,0.125,0.9375,1,0.875,1);
		break;
	case 5:
		if(source.getBlock(BlockPos(pos.x-1,pos.y,pos.z))==mBlocks[ID::mCable])
			return AABB(0,0,0,0.0625,1,1);
		return AABB(0,0.125,0,0.0625,0.875,1);
		break;
	case 4:
		if(source.getBlock(BlockPos(pos.x+1,pos.y,pos.z))==mBlocks[ID::mCable])
			return AABB(0.9375,0,0,1,1,1);
		return AABB(0.9375,0.125,0,1,0.875,1);
		break;
	}
	return AABB(0,0,0,1,0.0625,1);
}
const AABB &LuminatorActiveBlock::getVisualShape(unsigned char, AABB&, bool) const
{
	return AABB(0,0.001,0,1,0.0625,1);
}
int LuminatorActiveBlock::getPlacementDataValue(Entity&, BlockPos const&, signed char side, Vec3 const&, int) const
{
	return side+1;
}
#endif
