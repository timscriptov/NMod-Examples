#pragma once

#include "items/item/base/DischargeableEnergyStorageItem.h"

class ICRedstoneDustItem : public DischargeableEnergyStorageItem
{
public:
	ICRedstoneDustItem();
public:
	virtual unsigned long getMaxEnergy()const;
	virtual bool canCharge()const;
	virtual unsigned int getOVoltage()const;
	virtual std::string buildDescriptionName(ItemInstance const&) const;
	virtual bool _useOn(ItemInstance&, Entity&, BlockPos, signed char, float, float, float)const;
};
