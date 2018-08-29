#include "AuxDataCustomItem.h"

#include "mcpe/client/resources/I18n.h"

AuxDataCustomItem::AuxDataCustomItem(std::string const&name,short id):Item(name,id)
{
	setCategory(CreativeItemCategory::ITEMS);
	setStackedByData(true);
}
TextureUVCoordinateSet const& AuxDataCustomItem::getIcon(int aux, int i, bool z) const
{
	((Item*)this)->setIcon(aux==0?"bed":"snowball",0);
	
	return Item::getIcon(aux,i,z);
}
std::string AuxDataCustomItem::getInteractText(Player const&) const
{
	return I18n::get("interact.change");
}
std::string AuxDataCustomItem::buildDescriptionName(ItemInstance const&i) const
{
	return I18n::get("item."+((std::string)(i.aux==0?"magic_bed":"magic_snowball"))+".name");
}
bool AuxDataCustomItem::requiresInteract() const
{
	return true;
}
bool AuxDataCustomItem::use(ItemInstance&i, Player&p) const
{
	i.aux==0?i.aux=1:i.aux=0;
	return Item::use(i,p);
}
