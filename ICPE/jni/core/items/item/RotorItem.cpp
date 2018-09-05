#include "RotorItem.h"

RotorItem::RotorItem(std::string const&name,int id,std::string const& texture,int texID,int max):IC::Items(name,id)
{
	setIcon(texture,texID);
	setMaxStackSize(1);
	setMaxDamage(max);
}
