#pragma once

#include "items/Items.h"

class BronzeSwordItem : public IC::Items
{
public:
	BronzeSwordItem();
public:
	virtual int getEnchantSlot() const;
    virtual int getEnchantValue() const;
    virtual bool isValidRepairItem(ItemInstance const&, ItemInstance const&)const;
    virtual float getDestroySpeed(ItemInstance const&, Block const&)const;
    virtual void mineBlock(ItemInstance&, BlockID, int, int, int, Entity*)const;
    virtual void hurtEnemy(ItemInstance&, Mob*, Mob*)const;
    virtual int getAttackDamage()const;
    virtual bool canDestroySpecial(Block const&) const;
};
