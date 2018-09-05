#include "ElectricTreeTapItem.h"

#include "mcpe/item/ItemInstance.h"
#include "mcpe/block/Block.h"
#include "mcpe/entity/player/Player.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/util/FullBlock.h"
#include "mcpe/util/Util.h"
#include "mcpe/client/resources/I18n.h"
#include "mcpe/util/Random.h"

#include "blocks/Blocks.h"
#include "items/Items.h"

#include "ICPE.h"

ElectricTreeTapItem::ElectricTreeTapItem():EnergyStorageItem("electric_treetap",IC::Items::ID::mElectricTreeTap-0x100)
{
	setIcon("icpe_electric_treetap",0);
	setCategory(CreativeItemCategory::TOOLS);
	setHandEquipped();
}
unsigned long ElectricTreeTapItem::getMaxEnergy()const
{
	return 1E4;
}
bool ElectricTreeTapItem::_useOn(ItemInstance&item, Entity&e, BlockPos pos, signed char, float, float, float)const
{
	if(!hasEnergy(item,50))
		return false;
	if(hasEnergy(item,50)&&e.getRegion().getBlock(pos)==Block::mBlocks[IC::Blocks::ID::mRubberWood])
	{
		if(e.getRegion().getData(pos)>6)
		{
			e.getRegion().setBlockAndData(pos,FullBlock(IC::Blocks::ID::mRubberWood,e.getRegion().getData(pos)-4),3,0);
			costEnergy(item,50);
			//e.getRegion().getBlock(x,y,z)->popResource(e.getRegion(),BlockPos(x,y,z),ItemInstance(IC::Items::ID::mResin,1+ICPE::mRandom.nextInt(3),0));
		}
		else if(e.getRegion().getData(pos)>2)
		{
			e.getRegion().setBlockAndData(pos,FullBlock(IC::Blocks::ID::mRubberWood,0),3,0);
			costEnergy(item,50);
			//e.getRegion().getBlock(x,y,z)->popResource(e.getRegion(),BlockPos(x,y,z),ItemInstance(IC::Items::ID::mResin,1+ICPE::mRandom.nextInt(3),0));
		}
	}
	return false;
}
unsigned int ElectricTreeTapItem::getIVoltage()const
{
	return 5;
}
