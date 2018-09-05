#pragma once

#include "items/Items.h"
#include "mcpe/util/FullBlock.h"

class CableItem : public IC::Items
{
public:
	CableItem(std::string const&,short);
public:
    virtual std::string buildDescriptionName(ItemInstance const&) const;
    virtual TextureUVCoordinateSet const& getIcon(int, int, bool) const;
	virtual bool _useOn(ItemInstance&instance, Entity&p, BlockPos pos, signed char side, float pixelx, float pixely, float pixelz)const;
};
