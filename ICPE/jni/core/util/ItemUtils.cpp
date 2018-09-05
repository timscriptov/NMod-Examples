#include "ItemUtils.h"

#include <sstream>
#include <string>

#include "mcpe/item/ItemInstance.h"
#include "mcpe/util/Util.h"
#include "mcpe/nbt/CompoundTag.h"
#include "items/Items.h"
#include "mcpe/item/enchant/ItemEnchants.h"
#include "mcpe/item/enchant/EnchantUtils.h"

unsigned long ItemUtils::getMaxEnergy(ItemInstance const&item)
{
	if(!isICItem(item)||!isEnergyStorageItem(item))
		return 0;
	return IC::Items::mICItems[item.getId()]->getMaxEnergy();
}
bool ItemUtils::isICItem(ItemInstance const&item)
{
	return IC::Items::mICItems[item.getId()];
}
unsigned long ItemUtils::getEnergy(ItemInstance const&item)
{
	if(!isICItem(item)||!isEnergyStorageItem(item))
		return 0;
	return item.getBaseRepairCost();
}
bool ItemUtils::isEnergyStorageItem(ItemInstance const&item)
{
	if(!isICItem(item))
		return false;
	return IC::Items::mICItems[item.getId()]->isEnergyStorageItem();
}
bool ItemUtils::canCharge(ItemInstance const&item)
{
	if(!isICItem(item)||!isEnergyStorageItem(item))
		return false;
	return IC::Items::mICItems[item.getId()]->canCharge();
}
unsigned int ItemUtils::getIVoltage(ItemInstance const&item)
{
	if(!isICItem(item)||!isEnergyStorageItem(item))
		return 0;
	return IC::Items::mICItems[item.getId()]->getIVoltage();
}
unsigned int ItemUtils::getOVoltage(ItemInstance const&item)
{
	if(!isICItem(item)||!isEnergyStorageItem(item))
		return 0;
	return IC::Items::mICItems[item.getId()]->getOVoltage();
}
void ItemUtils::setEnergy(ItemInstance&item,unsigned long e)
{
	if(!isICItem(item)||!isEnergyStorageItem(item))
		return;
	item.setRepairCost(e);
	item.aux=32766*(1-(((float)e)/((float)getMaxEnergy(item))));
}
PainterAux ItemUtils::getPainterType(ItemInstance const&item)
{
	if(item.getId()!=IC::Items::ID::mPainter)
		return PainterAux::EMPTY;
	return (PainterAux)item.getBaseRepairCost();
}
void ItemUtils::setPainterType(ItemInstance&item,PainterAux e)
{
	if(item.getId()!=IC::Items::ID::mPainter)
		return;
	item.setRepairCost((int)e);
}
