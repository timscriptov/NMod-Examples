#pragma once

#include "mcpe/item/Item.h"

class AuxDataCustomItem : public Item
{
public:
	AuxDataCustomItem(std::string const&,short);
public:
    virtual TextureUVCoordinateSet const& getIcon(int, int, bool) const;
    virtual std::string getInteractText(Player const&) const;
    virtual std::string buildDescriptionName(ItemInstance const&) const;
    virtual bool requiresInteract() const;
    virtual bool use(ItemInstance&, Player&) const;
};
