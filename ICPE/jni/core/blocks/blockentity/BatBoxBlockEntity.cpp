#include "BatBoxBlockEntity.h"

#include <stdlib.h>
#include <cmath>

#include "mcpe/item/ItemInstance.h"
#include "mcpe/level/BlockSource.h"

#include "items/Items.h"
#include "blocks/Blocks.h"
#include "mca/data/Database.h"
#include "util/ItemUtils.h"
#include "util/Math.h"

BatBoxBlockEntity::BatBoxBlockEntity(BlockPos const&pos):ElectricMachineBlockEntity(pos,2)
{
	
}
void BatBoxBlockEntity::load(mca::CompoundTag const&tag)
{
	ElectricMachineBlockEntity::load(tag);
}
void BatBoxBlockEntity::save(mca::CompoundTag &tag)const
{
	ElectricMachineBlockEntity::save(tag);
}
void BatBoxBlockEntity::tick(Level&l,unsigned long long t)
{
	ElectricMachineBlockEntity::tick(l,t);
	
	if(getSlot(0)&&!getSlot(0)->isNull()&&getEnergy()>0&&ItemUtils::canCharge(*getSlot(0))&&ItemUtils::isEnergyStorageItem(*getSlot(0))&&(ItemUtils::getMaxEnergy(*getSlot(0))-ItemUtils::getEnergy(*getSlot(0)))>0)
	{
		unsigned long energyLast=0;
		unsigned long energyNeed=ItemUtils::getMaxEnergy(*getSlot(0))-ItemUtils::getEnergy(*getSlot(0));
		
		if(energyNeed==0)
			goto next;
		else if(getEnergy()>=energyNeed)
			energyLast=Math::min(ItemUtils::getIVoltage(*getSlot(0)),energyNeed);
		else if(getEnergy()<energyNeed)
			energyLast=Math::min(ItemUtils::getIVoltage(*getSlot(0)),getEnergy());
		else
			goto next;
		
		costEnergy(energyLast);
		ItemUtils::setEnergy(*getSlot(0),ItemUtils::getEnergy(*getSlot(0))+energyLast);
	}
	next:;
	
	if(canCharge())
	{
		if(ItemUtils::canCharge(*getSlot(1)))
		{
			unsigned int voltage=getItemVoltage(*getSlot(1));
			unsigned long energy=getItemEnergyLast(*getSlot(1));
			unsigned long energySholdMove;
			
			if(voltage>energy)
				energySholdMove=energy;
			else
				energySholdMove=voltage;
			
			if(getIVoltage()<energySholdMove)
				return explode();
			
			ItemUtils::setEnergy(*getSlot(1),ItemUtils::getEnergy(*getSlot(1))-energySholdMove);
			addEnergy(energySholdMove);
		}
		else if(canChargeWithDischargeable(*getSlot(1)))
		{
			unsigned int voltage=getItemVoltage(*getSlot(1));
			unsigned long energy=ItemUtils::getMaxEnergy(*getSlot(1));
			if(getIVoltage()<voltage)
				return explode();
		
			getSlot(1)->remove(1);
			addEnergy(energy);
		}
	}
	
	spreadEnergy(t);
}
bool BatBoxBlockEntity::canPushInItem(int s,ItemInstance const&i)
{
	if(getSlot(s)&&!getSlot(s)->isNull()&&getSlot(s)->getId()!=i.getId())
		return false;
	if(s==1&&ItemUtils::isEnergyStorageItem(i)&&ItemUtils::getOVoltage(i)>0)
		return true;
	if(s==0&&ItemUtils::isEnergyStorageItem(i)&&ItemUtils::canCharge(i))
		return true;
	return false;
}
float BatBoxBlockEntity::getEnergyProgress()const
{
	return ((float)getEnergy())/((float)getEnergyStorage());
}
unsigned long BatBoxBlockEntity::getEnergyStorageDefault()const
{
	return 40000;
}
bool BatBoxBlockEntity::isEnergyProvider(FacingEnum face)const
{
	/*short aux=getRegion().getData(pos)%6;
	switch(face)
	{
	case FacingEnum::UP:
		return aux==1;
	case FacingEnum::DOWN:
		return aux==0;
	case FacingEnum::WEST:
		return aux==5;
	case FacingEnum::EAST:
		return aux==4;
	case FacingEnum::NORTH:
		return aux==3;
	case FacingEnum::SOUTH:
		return aux==2;
	case FacingEnum::ANY:
		return true;
	}
	return false;*/
}
bool BatBoxBlockEntity::isEnergyReceiver(FacingEnum face)const
{
	if(face==FacingEnum::ANY)
		return true;
	return !isEnergyProvider(face);
}
unsigned int BatBoxBlockEntity::getOVoltage()const
{
	return 32;
}
unsigned int BatBoxBlockEntity::getIVoltage()const
{
	return 32;
}
bool BatBoxBlockEntity::canChargeWithDischargeable(ItemInstance const&item)
{
	if(!canCharge())
		return false;
	if(ItemUtils::isEnergyStorageItem(item)&&((IC::Items*)Item::mItems[item.getId()])->canCharge())
		return false;
	unsigned long lastEnergy=getEnergyStorage()-getEnergy();
	if(lastEnergy>=ItemUtils::getMaxEnergy(item))
		return true;
	if(getEnergy()==0)
		return true;
	return false;
}
unsigned int BatBoxBlockEntity::getItemVoltage(ItemInstance const&i)const
{
	return ItemUtils::getOVoltage(i);
}
unsigned long BatBoxBlockEntity::getItemEnergyLast(ItemInstance const&i)const
{
	return ItemUtils::getEnergy(i);
}
bool BatBoxBlockEntity::canCharge()
{
	if(getEnergy()>=getEnergyStorage())
		return false;
	if(getSlot(1)&&!getSlot(1)->isNull())
	{
		if(ItemUtils::isEnergyStorageItem(*getSlot(1))&&ItemUtils::getOVoltage(*getSlot(1))>0)
		{
			unsigned long lastEnergy=getEnergyStorage()-getEnergy();
			if(lastEnergy>=((IC::Items*)Item::mItems[getSlot(1)->getId()])->getOVoltage())
				return true;
			if(getEnergy()==0)
				return true;
			return false;
		}
	}
	return false;
}
