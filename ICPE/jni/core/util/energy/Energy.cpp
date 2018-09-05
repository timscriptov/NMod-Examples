#include "Energy.h"

#include "mca/data/Database.h"
#include "EnergyWeb.h"

Energy::Energy(unsigned long e,float f,unsigned int v)
{
	voltage=v;
	energy=e;
	energyF=f;
}
Energy::Energy()
{
	voltage=0;
	energyF=0.0F;
	energy=0;
}
void Energy::setVoltage(unsigned int v)
{
	voltage=v;
}
void Energy::setEnergy(unsigned long e)
{
	energy=e;
}
void Energy::setEnergyF(float e)
{
	energyF=e;
}
void Energy::addEnergy(unsigned long e)
{
	energy+=e;
}
void Energy::costEnergy(unsigned long e)
{
	if(e>=energy)
		energy=0;
	else
		energy-=e;
}
void Energy::addEnergyF(float e)
{
	energyF+=e;
	unsigned long shouldMove=(unsigned long)energyF;
	energyF-=shouldMove;
	addEnergy(shouldMove);
}
void Energy::costEnergyF(float e)
{
	energyF-=e;
	if(energyF<0)
	{
		costEnergy(energyF*-1+1);
		energyF=0;
	}
}
unsigned long Energy::getEnergy()const
{
	return energy;
}
float Energy::getEnergyF()const
{
	return energyF;
}
unsigned int Energy::getVoltage()const
{
	return voltage;
}
void Energy::save(mca::CompoundTag &tag)const
{
	tag.putUlong("icpe_energy_energy",energy);
	tag.putUint("icpe_energy_voltage",voltage);
	tag.putFloat("icpe_energy_energyF",energyF);
}
void Energy::load(mca::CompoundTag const&tag)
{
	energy=tag.getUlong("icpe_energy_energy");
	voltage=tag.getUint("icpe_energy_voltage");
	energyF=tag.getFloat("icpe_energy_energyF");
}
