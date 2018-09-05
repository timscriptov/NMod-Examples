#include "TreeTapItem.h"

#include "mcpe/item/ItemInstance.h"
#include "mcpe/block/Block.h"
#include "mcpe/entity/player/Player.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/util/FullBlock.h"
#include "mcpe/util/Random.h"

#include "blocks/Blocks.h"
#include "items/Items.h"

#include "ICPE.h"

TreeTapItem::TreeTapItem():IC::Items("treetap",IC::Items::ID::mTreeTap-0x100)
{
	setIcon("icpe_treetap",0);
	setMaxStackSize(1);
	setCategory(CreativeItemCategory::TOOLS);
	setMaxDamage(128);
}
bool TreeTapItem::_useOn(ItemInstance&item, Entity&e, BlockPos pos, signed char, float, float, float)const
{
	if(e.getRegion().getBlock(pos)==Block::mBlocks[IC::Blocks::ID::mRubberWood])
	{
		if(e.getRegion().getData(pos)>6)
		{
			e.getRegion().setBlockAndData(pos,FullBlock(IC::Blocks::ID::mRubberWood,e.getRegion().getData(pos)-4),3,0);
			item.hurtAndBreak(1,0);
			//e.getRegion().getBlock(x,y,z)->popResource(e.getRegion(),BlockPos(x,y,z),ItemInstance(IC::Items::ID::mResin,1+ICPE::mRandom.nextInt(3),0));
		}
		else if(e.getRegion().getData(pos)>2)
		{
			e.getRegion().setBlockAndData(pos,FullBlock(IC::Blocks::ID::mRubberWood,0),3,0);
			item.hurtAndBreak(1,0);
			//e.getRegion().getBlock(x,y,z)->popResource(e.getRegion(),BlockPos(x,y,z),ItemInstance(IC::Items::ID::mResin,1+ICPE::mRandom.nextInt(3),0));
		}
	}
	return false;
}
