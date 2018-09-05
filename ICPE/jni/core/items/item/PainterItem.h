#pragma once

#include "items/Items.h"

class PainterItem : public IC::Items
{
public:
	PainterItem();
public:
    virtual void interactEnemy(ItemInstance&, Mob*, Player*)const;
    virtual bool _useOn(ItemInstance&, Entity&, BlockPos, signed char, float, float, float)const;
	virtual std::string buildEffectDescriptionName(ItemInstance const&) const;
	virtual TextureUVCoordinateSet const& getIcon(int, int, bool) const;
};
