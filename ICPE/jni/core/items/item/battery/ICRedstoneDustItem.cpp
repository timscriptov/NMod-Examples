#include "ICRedstoneDustItem.h"

#include "mcpe/util/BlockPos.h"

ICRedstoneDustItem::ICRedstoneDustItem():DischargeableEnergyStorageItem("redstone",331-0x100)
{
	setIcon("redstone_dust",0);
	setCategory(CreativeItemCategory::TOOLS);
	setMaxStackSize(64);
}
unsigned long ICRedstoneDustItem::getMaxEnergy()const
{
	return 500;
}
bool ICRedstoneDustItem::canCharge()const
{
	return false;
}
unsigned int ICRedstoneDustItem::getOVoltage()const
{
	return 2;
}
bool ICRedstoneDustItem::_useOn(ItemInstance&instance, Entity&p, BlockPos pos, signed char side, float pixelx, float pixely, float pixelz)const
{
	ItemInstance blockItem(55,1,0);
	blockItem.useOn(p,pos.x,pos.y,pos.z,side,pixelx,pixely,pixelz);
	if(blockItem.isNull())
		instance.remove(1);
}
std::string ICRedstoneDustItem::buildDescriptionName(ItemInstance const&itemStack) const
{
	return Item::buildDescriptionName(itemStack);
}
