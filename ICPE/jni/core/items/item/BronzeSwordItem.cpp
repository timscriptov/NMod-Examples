#include "BronzeSwordItem.h"

BronzeSwordItem::BronzeSwordItem():IC::Items("bronze_sword",/*ID::mBronzeSword-*/0x100)
{
	setCategory(CreativeItemCategory::TOOLS);
	setIcon("icpe_bronze_sword",0);
	setMaxDamage(250);
	setHandEquipped();
	setMaxStackSize(1);
}
bool BronzeSwordItem::isValidRepairItem(ItemInstance const&, ItemInstance const&item)const
{
	//return item.getId()==ID::mBronzeAxe||item.getId()==ID::mBronzeIngot;
}
float BronzeSwordItem::getDestroySpeed(ItemInstance const&item, Block const&block)const
{
	return mSword_iron->getDestroySpeed(item,block)*1.2;
}
void BronzeSwordItem::mineBlock(ItemInstance&item, BlockID id, int x, int y, int z, Entity*e)const
{
	return mSword_iron->mineBlock(item,id,x,y,z,e);
}
int BronzeSwordItem::getEnchantSlot() const
{
	return mSword_iron->getEnchantSlot();
}
int BronzeSwordItem::getEnchantValue() const
{
	return mSword_iron->getEnchantValue();
}
void BronzeSwordItem::hurtEnemy(ItemInstance&item, Mob*m, Mob*mm)const
{
	return mSword_iron->hurtEnemy(item,m,mm);
}
int BronzeSwordItem::getAttackDamage()const
{
	return mSword_iron->getAttackDamage();
}
bool BronzeSwordItem::canDestroySpecial(Block const&b) const
{
	return mSword_iron->canDestroySpecial(b);
}
