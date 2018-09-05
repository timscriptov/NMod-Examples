#include "ElectricMachineBlockEntity.h"

#include "mcpe/level/Level.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/util/Vec3.h"
#include "mca/data/Database.h"
#include "items/Items.h"

ElectricMachineBlockEntity::ElectricMachineBlockEntity(BlockPos const&pos,int i)
:ICMachineBlockEntity(pos,i)
{
	eu=Energy();
}
void ElectricMachineBlockEntity::load(mca::CompoundTag const&tag)
{
	ICMachineBlockEntity::load(tag);
	eu.load(tag);
}
unsigned int ElectricMachineBlockEntity::getIVoltage()const
{
	return 0;
}
bool ElectricMachineBlockEntity::isElectricMachine()const
{
	return true;
}
unsigned int ElectricMachineBlockEntity::getOVoltage()const
{
	return 0;
}
void ElectricMachineBlockEntity::save(mca::CompoundTag &tag)const
{
	ICMachineBlockEntity::save(tag);
	eu.save(tag);
}
void ElectricMachineBlockEntity::tick(Level&l,unsigned long long t)
{
	ICMachineBlockEntity::tick(l,t);
	eu.setVoltage(getOVoltage());
}
void ElectricMachineBlockEntity::calculate(BlockSource&re)
{
	web=EnergyWeb(re,getPosition());
}
void ElectricMachineBlockEntity::spreadEnergy(unsigned long long t)
{
	web.spreadEnergy(eu,t);
}

void ElectricMachineBlockEntity::addEnergy(unsigned long e)
{
	unsigned long var=e+getEnergy();
	if(var<=getEnergyStorage())
		eu.addEnergy(e);
	else if(var>getEnergyStorage())
		eu.setEnergy(getEnergyStorage());
}
unsigned long ElectricMachineBlockEntity::getEnergyCanAdd(unsigned long l)
{
	unsigned long var=getEnergyStorage()-getEnergy();
	if(var>=l)
		return l;
	return var;
}
unsigned long ElectricMachineBlockEntity::getEnergyStorage()const
{
	if(energyStorageUpgrade)
		return getEnergyStorageDefault()*1.5F;
	return getEnergyStorageDefault();
}
unsigned long ElectricMachineBlockEntity::getEnergy()const
{
	return eu.getEnergy();
}
void ElectricMachineBlockEntity::setEnergy(unsigned long l)
{
	if(l<=getEnergyStorage())
		eu.setEnergy(l);
	else
		eu.setEnergy(getEnergyStorage());
}
void ElectricMachineBlockEntity::setVoltage(unsigned int i)
{
	eu.setVoltage(i);
}
unsigned int ElectricMachineBlockEntity::getVoltage()const
{
	return eu.getVoltage();
}
void ElectricMachineBlockEntity::costEnergy(unsigned long l)
{
	eu.costEnergy(l);
}
void ElectricMachineBlockEntity::addEnergyF(float f)
{
	eu.addEnergyF(f);
}
float ElectricMachineBlockEntity::getEnergyF()const
{
	return eu.getEnergyF();
}
void ElectricMachineBlockEntity::setEnergyF(float f)
{
	eu.setEnergyF(f);
}
void ElectricMachineBlockEntity::costEnergyF(float f)
{
	eu.costEnergyF(f);
}
