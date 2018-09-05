#pragma once

#include "base/EnergyStorageItem.h"

class ChainsawItem : public EnergyStorageItem
{
public:
	ChainsawItem();
public:
	virtual std::string buildEffectDescriptionName(ItemInstance const&) const;
	virtual std::string getInteractText(Player const&) const;
	virtual bool requiresInteract() const;
	virtual void onInteract(ItemInstance&)const;
	virtual void hurtEnemy(ItemInstance&, Mob*, Mob*)const;
	virtual int getAttackDamage()const;
	virtual std::string getLoopingSound(ItemInstance&)const;
    virtual void inventoryTick(ItemInstance&, Level&, Entity&, int, bool)const;
	virtual void mineBlock(ItemInstance&, BlockID, int, int, int, Entity*)const;
	virtual bool canDestroySpecial(const Block&) const;
	virtual float getDestroySpeed(ItemInstance const&, Block const&)const;
	virtual unsigned long getMaxEnergy()const;
	virtual unsigned int getIVoltage()const;
};
