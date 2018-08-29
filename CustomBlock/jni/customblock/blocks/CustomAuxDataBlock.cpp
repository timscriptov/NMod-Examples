#include "CustomAuxDataBlock.h"

#include "mcpe/entity/player/Player.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/util/FullBlock.h"

CustomAuxDataBlock::CustomAuxDataBlock(std::string const&name,int id):Block(name,id,Material::getMaterial(MaterialType::DEVICE))
{
	setCategory(CreativeItemCategory::BLOCKS);
	setVisualShape(AABB(0.4375,0,0.4375,0.5625,1,0.5625));
	setLightEmission(1.0);
	setExplodeable(1E2);
	setDestroyTime(-1);
	setSolid(false);
}
std::string CustomAuxDataBlock::buildDescriptionName(unsigned char aux) const
{
	return mWoodPlanks->buildDescriptionName(aux);
}
bool CustomAuxDataBlock::use(Player&player, BlockPos const&pos)const
{
	player.getRegion().setBlockAndData(pos,FullBlock(blockId,!player.getRegion().getData(pos)),3,0);
	return true;
}
