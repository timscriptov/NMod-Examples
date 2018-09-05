#pragma once

#include "items/Items.h"

class EnergyStorageItem : public IC::Items
{
public:
	EnergyStorageItem(std::string const&,short);
public:
	virtual unsigned long getEnergy(ItemInstance const&)const;
	virtual bool isEnergyStorageItem()const;
	virtual bool canCharge()const;
	virtual bool isValidRepairItem(ItemInstance const&, ItemInstance const&)const;
	virtual std::string buildEffectDescriptionName(const ItemInstance&) const;
public:
	void costEnergy(ItemInstance&,unsigned long)const;
	bool hasEnergy(ItemInstance const&,unsigned long)const;
};
