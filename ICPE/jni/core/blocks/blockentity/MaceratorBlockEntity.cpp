#include "MaceratorBlockEntity.h"

#include <stdlib.h>
#include <cmath>

#include "mcpe/item/ItemInstance.h"

#include "items/Items.h"
#include "blocks/Blocks.h"
#include "mca/data/Database.h"
#include "util/ItemUtils.h"
#include "items/recipe/MaceratorRecipes.h"

const float MaceratorBlockEntity::mSpeed=3.3333333E-3;
const unsigned long MaceratorBlockEntity::energyPerTick=2;

bool MaceratorBlockEntity::isEnergyReceiver(FacingEnum)const
{
	return true;
}
MaceratorBlockEntity::MaceratorBlockEntity(BlockPos const&pos):ElectricMachineBlockEntity(pos,3)
{
	burnProgress=0.0F;
	isLit_=false;
}
void MaceratorBlockEntity::load(mca::CompoundTag const&tag)
{
	ElectricMachineBlockEntity::load(tag);
	
	burnProgress=tag.getFloat("burnProgress");
	isLit_=tag.getBool("isLit");
}
void MaceratorBlockEntity::save(mca::CompoundTag &tag)const
{
	ElectricMachineBlockEntity::save(tag);
	
	tag.putFloat("burnProgress",(float)burnProgress);
	tag.putBool("isLit",(bool)isLit_);
}
void MaceratorBlockEntity::tick(Level&l,unsigned long long t)
{
	ElectricMachineBlockEntity::tick(l,t);
	if(burnProgress>=1.0F)
	{
		if(!getSlot(0)||getSlot(0)->isNull())
			goto burnEnd;
		ItemInstance item=MaceratorRecipes::getInstance()->getResult(getSlot(0));
		if(item.isNull())
			goto burnEnd;
		if(!getSlot(2)||getSlot(2)->isNull())
			setSlot(2,&item);
		else
			getSlot(2)->add(item.count);
		getSlot(0)->remove(1);
		burnProgress=0.0F;
	}
	else if(burnProgress>0.0F&&burnProgress<1.0F)
	{
		if(canBurn())
			burnProgress+=mSpeed;
		else if(!getSlot(0)||getSlot(0)->isNull())
			burnProgress=0.0F;
		else
			burnProgress-=(mSpeed*2);
	}
	else if(burnProgress==0.0F)
	{
		if(canBurn())
			burnProgress=mSpeed;
	}
	else
		burnProgress=0.0F;
	
	burnEnd:;
	
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
	
	if(burnProgress>0&&!isLit())
		setLit(true);
	else if(burnProgress<=0&&isLit())
		setLit(false);
	
	if(getEnergy()>=energyPerTick&&isLit())
		costEnergy(energyPerTick);
}
bool MaceratorBlockEntity::isLit()const
{
	return isLit_;
}
unsigned int MaceratorBlockEntity::getIVoltage()const
{
	return 32;
}
void MaceratorBlockEntity::setLit(bool b)
{
	isLit_=b;
	//update();
}
bool MaceratorBlockEntity::canChargeWithDischargeable(ItemInstance const&item)
{
	if(!canCharge())
		return false;
	if(ItemUtils::isEnergyStorageItem(item)&&((IC::Items*)Item::mItems[item.getId()])->canCharge())
		return false;
	unsigned long lastEnergy=getEnergyStorage()-getEnergy();
	if(lastEnergy>=ItemUtils::getMaxEnergy(item))
		return true;
	if(getEnergy()<energyPerTick)
		return true;
	return false;
}
bool MaceratorBlockEntity::canPushInItem(int s,ItemInstance const&i)
{
	if(getSlot(s)&&!getSlot(s)->isNull()&&getSlot(s)->getId()!=i.getId())
		return false;
	if(s==1&&ItemUtils::isEnergyStorageItem(i)&&ItemUtils::getOVoltage(i)>0)
		return true;
	if(s==0)
		return true;
	return false;
}
float MaceratorBlockEntity::getWorkProgress()const
{
	if(burnProgress>=0.0F)
		return burnProgress;
	return 0.0F;
}
float MaceratorBlockEntity::getElectricProgress()const
{
	if(getEnergy()<=0)
		return 0.0F;
	return ((float)getEnergy())/((float)getEnergyStorage());
}
unsigned int MaceratorBlockEntity::getItemVoltage(ItemInstance const&i)const
{
	return ItemUtils::getOVoltage(i);
}
unsigned long MaceratorBlockEntity::getItemEnergyLast(ItemInstance const&i)const
{
	return ItemUtils::getEnergy(i);
}
bool MaceratorBlockEntity::canBurn()
{
	if(getEnergy()<energyPerTick)
		return false;
	if(!getSlot(0)||getSlot(0)->isNull())
		return false;
	if(MaceratorRecipes::mInstance->isMaceratorItem(getSlot(0)))
	{
		if(getSlot(2)&&!getSlot(2)->isNull())
		{
			if(MaceratorRecipes::getInstance()->getResult(getSlot(0)).sameItemAndAux(*getSlot(2))&&!getSlot(2)->isFullStack())
			{
				ItemInstance item=*getSlot(2);
				item.add(MaceratorRecipes::getInstance()->getResult(getSlot(0)).count);
				return !item.isFullStack();
			}
			return false;
		}
		else
			return true;
	}
	return false;
}
bool MaceratorBlockEntity::canCharge()
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
			if(getEnergy()<energyPerTick)
				return true;
			return false;
		}
	}
	return false;
}
unsigned long MaceratorBlockEntity::getEnergyStorageDefault()const
{
	return 1200;
}
