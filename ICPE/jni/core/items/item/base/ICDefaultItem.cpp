#include "ICDefaultItem.h"

ICDefaultItem::ICDefaultItem(std::string const&name,short id,std::string const&iconName,int iconAux):IC::Items(name,id)
{
	setCategory(CreativeItemCategory::ITEMS);
	setIcon(iconName,iconAux);
}
ICDefaultItem::ICDefaultItem(std::string const&name,short id,TextureUVCoordinateSet const&texture):IC::Items(name,id)
{
	setCategory(CreativeItemCategory::ITEMS);
	setIcon(texture);
}
