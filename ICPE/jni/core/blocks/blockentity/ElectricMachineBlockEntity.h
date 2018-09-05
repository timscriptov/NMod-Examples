#pragma once

#include "ICMachineBlockEntity.h"

class ElectricMachineBlockEntity : public ICMachineBlockEntity
{
protected:
	Energy eu;
	EnergyWeb web;
public:
	ElectricMachineBlockEntity(BlockPos const&,int);
	~ElectricMachineBlockEntity()=default;
public:
	void spreadEnergy(unsigned long long);
	virtual unsigned long getEnergyStorageDefault()const=0;
	virtual unsigned int getIVoltage()const;
	virtual unsigned int getOVoltage()const;
	virtual void load(mca::CompoundTag const&);
	virtual void save(mca::CompoundTag &)const;
	virtual void tick(Level&,unsigned long long);
	void calculate(BlockSource&);
	unsigned long getEnergyStorage()const;
	void addEnergy(unsigned long);
	unsigned long getEnergy()const;
	void setEnergy(unsigned long);
	void addEnergyF(float);
	float getEnergyF()const;
	void setEnergyF(float);
	void costEnergyF(float);
	void setVoltage(unsigned int);
	unsigned int getVoltage()const;
	void costEnergy(unsigned long);
	unsigned long getEnergyCanAdd(unsigned long);
	bool isElectricMachine()const;
};
