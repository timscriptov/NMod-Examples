#include "ExtendsItem.h"

ExtendsItem::ExtendsItem(std::string const&name,short id):Item(name,id)
{
	setCategory(CreativeItemCategory::ITEMS);
}
