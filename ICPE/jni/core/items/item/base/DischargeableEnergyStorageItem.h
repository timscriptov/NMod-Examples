#pragma once

#include "items/Items.h"

class DischargeableEnergyStorageItem : public IC::Items
{
public:
	DischargeableEnergyStorageItem(std::string const&,short);
public:
	virtual unsigned long getEnergy(ItemInstance const&)const;
	virtual bool isEnergyStorageItem()const;
	virtual bool canCharge()const;
	virtual bool isValidRepairItem(ItemInstance const&, ItemInstance const&);
	virtual std::string buildEffectDescriptionName(const ItemInstance&) const;
};
