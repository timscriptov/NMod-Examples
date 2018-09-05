#pragma once

#include "base/EnergyStorageItem.h"

class ElectricWrenchItem : public EnergyStorageItem
{
public:
	ElectricWrenchItem();
public:
	virtual unsigned long getMaxEnergy()const;
	virtual unsigned int getIVoltage()const;
	virtual float getDestroySpeed(ItemInstance const&, Block const&)const;
    virtual bool _useOn(ItemInstance&, Entity&, BlockPos, signed char, float, float, float)const;
};
