#include "EnergyStorageItem.h"

#include "mcpe/client/resources/I18n.h"
#include "mcpe/util/Util.h"
#include "mcpe/nbt/CompoundTag.h"
#include "util/ItemUtils.h"

EnergyStorageItem::EnergyStorageItem(std::string const&name,short id):IC::Items(name,id)
{
	setCategory(CreativeItemCategory::TOOLS);
	setMaxStackSize(1);
	setMaxDamage(32767);
}
std::string EnergyStorageItem::buildEffectDescriptionName(const ItemInstance&i) const
{
	return "§7"+I18n::get("item.CrystalMemory.tooltip.Energy")+Util::toString(ItemUtils::getEnergy(i))+"EU/"+Util::toString(ItemUtils::getMaxEnergy(i))+"EU";
}
bool EnergyStorageItem::isValidRepairItem(ItemInstance const&, ItemInstance const&)const
{
	return false;
}
unsigned long EnergyStorageItem::getEnergy(ItemInstance const&item)const
{
	return ItemUtils::getEnergy(item);
}
void EnergyStorageItem::costEnergy(ItemInstance&i,unsigned long e)const
{
	if(ItemUtils::getEnergy(i)>=e)
		ItemUtils::setEnergy(i,ItemUtils::getEnergy(i)-e);
	else
		ItemUtils::setEnergy(i,0);
}
bool EnergyStorageItem::hasEnergy(ItemInstance const&i,unsigned long e)const
{
	return ItemUtils::getEnergy(i)>=e;
}
bool EnergyStorageItem::isEnergyStorageItem()const
{
	return true;
}
bool EnergyStorageItem::canCharge()const
{
	return true;
}
