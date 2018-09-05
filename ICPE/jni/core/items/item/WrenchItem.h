#pragma once

#include "items/Items.h"

class WrenchItem : public IC::Items
{
public:
	WrenchItem();
public:
    virtual float getDestroySpeed(ItemInstance const&, Block const&)const;
    virtual bool _useOn(ItemInstance&, Entity&, BlockPos, signed char, float, float, float)const;
};
