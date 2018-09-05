#pragma once

#include "items/Items.h"

class MeterItem : public IC::Items
{
public:
	MeterItem();
public:
	virtual bool _useOn(ItemInstance&, Entity&, BlockPos, signed char, float, float, float)const;
};
