#include "DischargeableEnergyStorageItem.h"

#include "mcpe/client/resources/I18n.h"
#include "mcpe/util/Util.h"
#include "mcpe/nbt/CompoundTag.h"
#include "util/ItemUtils.h"

DischargeableEnergyStorageItem::DischargeableEnergyStorageItem(std::string const&name,short id):IC::Items(name,id)
{
	setCategory(CreativeItemCategory::TOOLS);
	setMaxStackSize(64);
}
std::string DischargeableEnergyStorageItem::buildEffectDescriptionName(const ItemInstance&i) const
{
	return "§7"+I18n::get("item.CrystalMemory.tooltip.Energy")+Util::toString(ItemUtils::getMaxEnergy(i))+"EU";
}
bool DischargeableEnergyStorageItem::isValidRepairItem(ItemInstance const&, ItemInstance const&)
{
	return false;
}
unsigned long DischargeableEnergyStorageItem::getEnergy(ItemInstance const&item)const
{
	return ItemUtils::getMaxEnergy(item);
}
bool DischargeableEnergyStorageItem::isEnergyStorageItem()const
{
	return true;
}
bool DischargeableEnergyStorageItem::canCharge()const
{
	return false;
}
