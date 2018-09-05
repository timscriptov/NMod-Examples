#include "BronzeHoeItem.h"

#include "mcpe/util/BlockPos.h"

BronzeHoeItem::BronzeHoeItem():IC::Items("bronze_hoe",/*ID::mBronzeHoe*/-0x100)
{
	setCategory(CreativeItemCategory::TOOLS);
	setIcon("icpe_bronze_hoe",0);
	setMaxDamage(250);
	setHandEquipped();
	setMaxStackSize(1);
}
bool BronzeHoeItem::isValidRepairItem(ItemInstance const&, ItemInstance const&item)const
{
	//return item.getId()==ID::mBronzeHoe||item.getId()==ID::mBronzeIngot;
}
bool BronzeHoeItem::_useOn(ItemInstance&item, Entity&e, BlockPos pos, signed char side, float pixelx, float pixely, float pixelz) const
{
	return mHoe_iron->_useOn(item,e,pos,side,pixelx,pixely,pixelz);
}
int BronzeHoeItem::getEnchantSlot() const
{
	return mHoe_iron->getEnchantSlot();
}
int BronzeHoeItem::getEnchantValue() const
{
	return mHoe_iron->getEnchantValue();
}
