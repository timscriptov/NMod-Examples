#pragma once

class BlockPos;
class BlockSource;

namespace mca
{
	class CompoundTag;
}

class Energy
{
private:
	unsigned long energy;
	unsigned int voltage;
	float energyF;
public:
	Energy();
	Energy(unsigned long,float,unsigned int);
	~Energy()=default;
public:
	void setVoltage(unsigned int);
	void setEnergy(unsigned long);
	void setEnergyF(float);
	void addEnergy(unsigned long);
	void costEnergy(unsigned long);
	void addEnergyF(float);
	void costEnergyF(float);
	unsigned long getEnergy()const;
	unsigned int getVoltage()const;
	float getEnergyF()const;
	void save(mca::CompoundTag &)const;
	void load(mca::CompoundTag const&);
};
