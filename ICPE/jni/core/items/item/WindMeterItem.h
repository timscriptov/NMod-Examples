#pragma once

#include "base/EnergyStorageItem.h"

class WindMeterItem : public EnergyStorageItem
{
public:
	WindMeterItem();
public:
	virtual unsigned long getMaxEnergy()const;
	virtual unsigned int getIVoltage()const;
    virtual bool use(ItemInstance&, Player&)const;
    virtual std::string getInteractText(Player const&) const;
	virtual bool requiresInteract() const;
};
