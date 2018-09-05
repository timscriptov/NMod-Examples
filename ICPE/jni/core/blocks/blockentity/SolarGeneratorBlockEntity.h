#pragma once

class ItemInstance;

#include "ElectricMachineBlockEntity.h"

class SolarGeneratorBlockEntity : public ElectricMachineBlockEntity
{
public:
	float progress;
	float lastSpeed;
public:
	SolarGeneratorBlockEntity(BlockPos const&);
	~SolarGeneratorBlockEntity()=default;
public:
	virtual void load(mca::CompoundTag const&);
	virtual void save(mca::CompoundTag &)const;
	virtual void tick(Level&,unsigned long long);
	virtual unsigned long getEnergyStorageDefault()const;
public:
	unsigned int getNowOutVoltage()const;
	float getNowEUEveryTick(unsigned long long);
	bool isActive()const;
	bool canPushInItem(ItemInstance const&);
	bool isEnergyProvider(FacingEnum)const;
};
