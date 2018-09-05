#include "WrenchItem.h"

#include "mcpe/item/ItemInstance.h"
#include "mcpe/block/Block.h"
#include "mcpe/entity/player/Player.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/util/FullBlock.h"
#include "mcpe/util/Util.h"
#include "mcpe/client/resources/I18n.h"
#include "mcpe/util/Random.h"

#include "blocks/Blocks.h"
#include "mca/data/Database.h"
#include "items/Items.h"
#include "blocks/blockentity/ICBlockEntity.h"

#include "ICPE.h"

WrenchItem::WrenchItem():IC::Items("wrench",IC::Items::ID::mWrench-0x100)
{
	setIcon("icpe_wrench",0);
	setMaxDamage(300);
	setMaxStackSize(1);
	setCategory(CreativeItemCategory::TOOLS);
	setHandEquipped();
}
float WrenchItem::getDestroySpeed(ItemInstance const&, Block const&)const
{
	return -1;
}
bool WrenchItem::_useOn(ItemInstance&item, Entity&e, BlockPos pos, signed char side, float, float, float)const
{
	if(!IC::Blocks::mICBlocks[e.getRegion().getBlock(pos)->blockId]||!IC::Blocks::mICBlocks[e.getRegion().getBlock(pos)->blockId]->isMachineBlock(e.getRegion(),BlockPos(pos))||(!IC::Blocks::mICBlocks[e.getRegion().getBlock(pos)->blockId]->isAllFace()&&(side==0||side==1)))
		return false;
	item.hurtAndBreak(1,0);
	if(IC::Blocks::mICBlocks[e.getRegion().getBlock(pos)->blockId]->isAllFace())
	{
		switch(side)
		{
		case 2:
			side=3;
		break;
		case 3:
			side=2;
		break;
		case 4:
			side=5;
		break;
		case 5:
			side=4;
		break;
		}
	}
	
	/*int aux;
	if(IC::Blocks::mICBlocks[e.getRegion().getBlock(x,y,z)->blockId]->isAllFace())
		aux=e.getRegion().getData(x,y,z)-e.getRegion().getData(x,y,z)%6+side;
	else
		aux=e.getRegion().getData(x,y,z)-e.getRegion().getData(x,y,z)%4+side-2;
	mca::CompoundTag tag;
	e.getRegion().getBlockEntity(x,y,z)->save(tag);
	e.getRegion().getBlockEntity(x,y,z)->reset();
	e.getRegion().setBlockAndData(x,y,z,FullBlock(e.getRegion().getBlock(x,y,z)->blockId,aux),3);
	e.getRegion().getBlockEntity(x,y,z)->load(tag);*/
	return false;
}
