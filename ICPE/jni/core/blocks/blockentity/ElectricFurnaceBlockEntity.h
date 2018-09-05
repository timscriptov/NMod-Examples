#pragma once

#include "ElectricMachineBlockEntity.h"

class ElectricFurnaceBlockEntity : public ElectricMachineBlockEntity
{
private:
	bool isLit_;
	float burnProgress;
public:
	ElectricFurnaceBlockEntity(BlockPos const&);
	~ElectricFurnaceBlockEntity()=default;
public:
	virtual void load(mca::CompoundTag const&);
	virtual void save(mca::CompoundTag &)const;
	virtual void tick(Level&,unsigned long long);
	virtual unsigned int getIVoltage()const;
	virtual bool isEnergyReceiver(FacingEnum)const;
	virtual unsigned long getEnergyStorageDefault()const;
public:
	bool canPushInItem(int,ItemInstance const&);
	bool isLit()const;
	void setLit(bool);
	float getBurnProgress()const;
	float getElectricProgress()const;
	bool canBurn();
	bool canCharge();
	bool canChargeWithDischargeable(ItemInstance const&);
	unsigned int getItemVoltage(ItemInstance const&)const;
	unsigned long getItemEnergyLast(ItemInstance const&)const;
public:
	static const float mSpeed;
	static const unsigned long energyPerTick;
};
