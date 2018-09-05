#pragma once

#include "base/EnergyStorageItem.h"

class ElectricTreeTapItem : public EnergyStorageItem
{
public:
	ElectricTreeTapItem();
public:
	virtual unsigned long getMaxEnergy()const;
	virtual unsigned int getIVoltage()const;
	virtual bool _useOn(ItemInstance&, Entity&, BlockPos, signed char, float, float, float)const;
};
