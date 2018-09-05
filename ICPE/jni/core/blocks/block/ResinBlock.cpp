#include "ResinBlock.h"

#include "items/Items.h"
#include "blocks/Blocks.h"

#include "mcpe/item/ItemInstance.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/level/Level.h"
#include "mcpe/entity/Entity.h"
#include "mcpe/client/resources/I18n.h"

ResinBlock::ResinBlock():IC::Blocks("sheet.rubber",IC::Blocks::ID::mResin,Material::getMaterial(MaterialType::DEVICE))
{
	init();
	setCategory(CreativeItemCategory::DECORATIONS);
	setVisualShape({0,0,0,1,0.25,1});
	setDestroyTime(1);
	setSolid(false);
}
int ResinBlock::getSpawnResourcesAuxValue(unsigned char aux)const
{
	return aux;
}
bool ResinBlock::mayPlaceOn(Block const&b)const
{
	return b.isSolid();
}
void ResinBlock::neighborChanged(BlockSource&s, BlockPos const&pos, BlockPos const&)const
{
	if(s.getBlock(pos)==this&&!mayPlaceOn(*s.getBlock(pos.x,pos.y-1,pos.z)))
	{
		s.getLevel().destroyBlock(s,pos,true);
	}
}
void ResinBlock::onFallOn(BlockSource&s, BlockPos const&pos, Entity*entity, float distance) const
{
	if(s.getData(pos)==1)
		mSlimeBlock->onFallOn(s,pos,entity,distance);
}
void ResinBlock::onStepOn(Entity&e, BlockPos const&pos) const
{
	if(e.getRegion().getData(pos)==0)
		mSlimeBlock->onStepOn(e,pos);
}
void ResinBlock::onPlace(BlockSource&s, BlockPos const&pos) const
{
	if(s.getBlock(pos)==this&&!mayPlaceOn(*s.getBlock(pos.x,pos.y-1,pos.z)))
	{
		s.getLevel().destroyBlock(s,pos,true);
	}
}
std::string ResinBlock::buildDescriptionName(unsigned char aux) const
{
	return I18n::get(aux?"sheet.rubber":"misc_resource.resin");
}
