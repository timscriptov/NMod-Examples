#pragma once

#include "items/item/base/DischargeableEnergyStorageItem.h"

class SingleUseBatteryItem : public DischargeableEnergyStorageItem
{
public:
	SingleUseBatteryItem();
public:
	virtual unsigned long getMaxEnergy()const;
	virtual bool canCharge()const;
	virtual unsigned int getOVoltage()const;
};
