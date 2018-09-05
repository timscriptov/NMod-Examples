#pragma once

#include "items/Items.h"

class ForgeHammerItem : public IC::Items
{
public:
	ForgeHammerItem();
public:
    virtual void onCraftedBy(ItemInstance&, Level&, Player&)const;
};
