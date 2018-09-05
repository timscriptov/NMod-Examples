#pragma once

#include "base/EnergyStorageItem.h"

class DischargedChainsawItem : public EnergyStorageItem
{
public:
	DischargedChainsawItem();
public:
    virtual std::string buildEffectDescriptionName(ItemInstance const&) const;
	virtual std::string getInteractText(Player const&) const;
	virtual bool requiresInteract() const;
	virtual void onInteract(ItemInstance&)const;
    virtual void inventoryTick(ItemInstance&, Level&, Entity&, int, bool)const;
	virtual void mineBlock(ItemInstance&, BlockID, int, int, int, Entity*)const;
	virtual bool canDestroySpecial(const Block&) const;
	virtual float getDestroySpeed(ItemInstance const&, Block const&)const;
	virtual unsigned long getMaxEnergy()const;
	virtual unsigned int getIVoltage()const;
};
