#pragma once

#include "items/Items.h"

class ICDefaultItem : public IC::Items
{
public:
	ICDefaultItem(std::string const&,short,TextureUVCoordinateSet const&);
	ICDefaultItem(std::string const&,short,std::string const&,int);
};
