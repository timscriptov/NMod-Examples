#pragma once

#include "ElectricMachineBlockEntity.h"

class LuminatorBlockEntity : public ElectricMachineBlockEntity
{
private:
	bool isLit_;
public:
	LuminatorBlockEntity(BlockPos const&);
	~LuminatorBlockEntity()=default;
public:
	virtual void load(mca::CompoundTag const&);
	virtual void save(mca::CompoundTag &)const;
	virtual void tick(Level&,unsigned long long);
	virtual unsigned int getIVoltage()const;
	virtual bool isEnergyReceiver(FacingEnum)const;
	virtual unsigned long getEnergyStorageDefault()const;
public:
	bool canPushInItem(ItemInstance const&);
	bool isLit()const;
	void setLit(bool);
	float getEnergyStorageProgress()const;
	bool canBurn();
	bool canCharge();
	bool canChargeWithDischargeable(ItemInstance const&);
	unsigned int getItemVoltage(ItemInstance const&)const;
	unsigned long getItemEnergyLast(ItemInstance const&)const;
public:
	static void setBlockToLit(LuminatorBlockEntity*,bool);
	static const float energyPerTick;
};
