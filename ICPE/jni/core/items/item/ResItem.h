#pragma once

#include "items/Items.h"

class ResItem : public IC::Items
{
private:
	static std::vector<std::string> mItemNameIDs;
public:
	ResItem();
public:
    virtual std::string buildDescriptionName(ItemInstance const&) const;
	virtual TextureUVCoordinateSet const& getIcon(int, int, bool) const;
};
