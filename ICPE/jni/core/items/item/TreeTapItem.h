#pragma once

#include "items/Items.h"

class TreeTapItem : public IC::Items
{
public:
	TreeTapItem();
public:
	virtual bool _useOn(ItemInstance&, Entity&, BlockPos, signed char, float, float, float)const;
};
