#pragma once

#include "ElectricMachineBlockEntity.h"

class BatBoxBlockEntity : public ElectricMachineBlockEntity
{
public:
	BatBoxBlockEntity(BlockPos const&);
	~BatBoxBlockEntity()=default;
public:
	virtual void load(mca::CompoundTag const&);
	virtual void save(mca::CompoundTag &)const;
	virtual void tick(Level&,unsigned long long);
	virtual unsigned long getEnergyStorageDefault()const;
public:
	bool canPushInItem(int,ItemInstance const&);
	float getEnergyProgress()const;
	bool isEnergyProvider(FacingEnum)const;
	bool isEnergyReceiver(FacingEnum)const;
	unsigned int getIVoltage()const;
	unsigned int getOVoltage()const;
	bool canCharge();
	bool canChargeWithDischargeable(ItemInstance const&);
	unsigned int getItemVoltage(ItemInstance const&)const;
	unsigned long getItemEnergyLast(ItemInstance const&)const;
public:
	static const float mSpeed;
};
