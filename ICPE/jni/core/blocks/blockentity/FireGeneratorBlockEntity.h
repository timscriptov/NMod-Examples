#pragma once

#include "ElectricMachineBlockEntity.h"

class FireGeneratorBlockEntity : public ElectricMachineBlockEntity
{
private:
	bool isLit_;
	int fireProgress;
	int maxFireProgress;
public:
	FireGeneratorBlockEntity(BlockPos const&);
	~FireGeneratorBlockEntity()=default;
public:
	virtual void load(mca::CompoundTag const&);
	virtual void save(mca::CompoundTag &)const;
	virtual void tick(Level&,unsigned long long);
	virtual unsigned long getEnergyStorageDefault()const;
public:
	bool canPushInItem(int,ItemInstance const&);
	bool isLit()const;
	void setLit(bool);
	float getEnergyProgress()const;
	float getFireProgress()const;
	bool canBurn();
	bool canStartNextFire();
	int getBurnDuration(ItemInstance const*)const;
	bool isEnergyProvider(FacingEnum)const;
	unsigned int getOVoltage()const;
public:
	static const float mSpeed;
};
