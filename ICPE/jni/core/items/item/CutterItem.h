#pragma once

#include "items/Items.h"

class CutterItem : public IC::Items
{
public:
	CutterItem();
public:
    virtual void onCraftedBy(ItemInstance&, Level&, Player&)const;
};
