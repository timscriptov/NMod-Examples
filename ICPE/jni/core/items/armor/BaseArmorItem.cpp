#include "BaseArmorItem.h"

#include "mcpe/client/resources/I18n.h"
#include "mcpe/item/ItemInstance.h"

BaseArmorItem::BaseArmorItem(int i,std::string const&n,std::string const&t,int ii,int d,ArmorItem::ArmorMaterial&m,ArmorSlot s,unsigned short reid):ArmorItem(n,i,m,0,s)
{
	descriptionName=n;
	setIcon(t,ii);
	setMaxDamage(d);
	repairItemID=reid;
	setCategory(CreativeItemCategory::TOOLS);
}
std::string BaseArmorItem::buildDescriptionName(ItemInstance const&) const
{
	return I18n::get(descriptionName);
}
bool BaseArmorItem::isValidRepairItem(ItemInstance const&i, ItemInstance const&i2)
{
	return ArmorItem::isValidRepairItem(i,i2)||i2.getId()==repairItemID;
}
