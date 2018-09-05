#pragma once

#include "items/Items.h"

class BronzeShovelItem : public IC::Items
{
public:
	BronzeShovelItem();
public:
	virtual int getEnchantSlot() const;
    virtual int getEnchantValue() const;
    virtual bool isValidRepairItem(ItemInstance const&, ItemInstance const&)const;
    virtual float getDestroySpeed(ItemInstance const&, Block const&)const;
    virtual void mineBlock(ItemInstance&, BlockID, int, int, int, Entity*)const;
    virtual bool _useOn(ItemInstance&, Entity&, BlockPos, signed char, float, float, float)const;
};
