#if 0
#include "BaseMachineBlock.h"

#include "items/Items.h"
#include "util/ItemUtils.h"
#include "mcpe/util/Random.h"
#include "mcpe/level/level.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/entity/player/Player.h"
#include "ICPE.h"

BaseMachineBlock::BaseMachineBlock(const std::string&name, int id, const Material&m):CEntityBlock(name,id,m)
{
	
}
bool BaseMachineBlock::isAnyAuxValueInRecipe()const
{
	return false;
}
int BaseMachineBlock::getResource(Random&, int, int)const
{
	return 0;
}
int BaseMachineBlock::getResourceCount(Random&, int, int)const
{
	return 0;
}
bool BaseMachineBlock::canBeSilkTouched() const
{
	return true;
}
void BaseMachineBlock::spawnResources(BlockSource&s, BlockPos const&pos, int, float, int aux) const
{
	std::vector<ItemInstance> res=getSpawnResources(aux,ICPE::mRandom);
	
	for(ItemInstance item:res)
		if(!item.isNull())
			popResource(s,pos,item);
}
int BaseMachineBlock::getSpawnResourcesAuxValue(unsigned char aux)const
{
	return aux/(isAllFace()?6:4);
}
std::vector<ItemInstance> BaseMachineBlock::getSpawnResources(int,Random&)const
{
	return std::vector<ItemInstance>();
}
bool BaseMachineBlock::use(Player&p, BlockPos const&pos) const
{
	ItemInstance* item=p.getSelectedItem();
	if(!item||item->isNull())
		return false;
	ItemInstance copyItem=*item;
	if(p.isSurvival()&&copyItem.getId()==IC::Items::ID::mWrench)
		item->hurtAndBreak(5,0);
	else if(p.isSurvival()&&copyItem.getId()==IC::Items::ID::mElectricWrench)
	{
		if(ItemUtils::getEnergy(*item)>=2500)
			ItemUtils::setEnergy(*item,ItemUtils::getEnergy(*item)-2500);
		else
			return false;
	}
	else if(copyItem.getId()!=IC::Items::ID::mElectricWrench&&copyItem.getId()!=IC::Items::ID::mWrench)
		return false;
	if(copyItem.getId()==IC::Items::ID::mElectricWrench||!ICPE::mRandom.nextBool(5))
		popResource(p.getRegion(),pos,getSilkTouchItemInstance(p.getRegion().getData(pos)));
	else
		spawnResources(p.getRegion(),pos,0,0,p.getRegion().getData(pos));
	p.getRegion().getLevel().destroyBlock(p.getRegion(),pos,false);
	return true;
}
bool BaseMachineBlock::isMachineBlock(BlockSource&,BlockPos const&)const
{
	return true;
}
#endif
