#include "BronzeShovelItem.h"

#include "mcpe/util/BlockPos.h"

BronzeShovelItem::BronzeShovelItem():IC::Items("bronze_shovel",/*ID::mBronzeShovel-*/0x100)
{
	setCategory(CreativeItemCategory::TOOLS);
	setIcon("icpe_bronze_shovel",0);
	setMaxDamage(250);
	setHandEquipped();
	setMaxStackSize(1);
}
bool BronzeShovelItem::isValidRepairItem(ItemInstance const&, ItemInstance const&item)const
{
	//return item.getId()==ID::mBronzeShovel||item.getId()==ID::mBronzeIngot;
}
float BronzeShovelItem::getDestroySpeed(ItemInstance const&item, Block const&block)const
{
	return mShovel_iron->getDestroySpeed(item,block)*1.2;
}
void BronzeShovelItem::mineBlock(ItemInstance&item, BlockID id, int x, int y, int z, Entity*e)const
{
	return mShovel_iron->mineBlock(item,id,x,y,z,e);
}
bool BronzeShovelItem::_useOn(ItemInstance&item, Entity&e, BlockPos pos, signed char side, float pixelx, float pixely, float pixelz)const
{
	return mShovel_iron->_useOn(item,e,pos,side,pixelx,pixely,pixelz);
}
int BronzeShovelItem::getEnchantSlot() const
{
	return mShovel_iron->getEnchantSlot();
}
int BronzeShovelItem::getEnchantValue() const
{
	return mShovel_iron->getEnchantValue();
}
