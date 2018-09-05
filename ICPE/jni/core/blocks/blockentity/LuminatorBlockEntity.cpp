#include "LuminatorBlockEntity.h"

#include <stdlib.h>
#include <cmath>

#include "mcpe/item/ItemInstance.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/level/Level.h"
#include "mcpe/util/FullBlock.h"
#include "items/Items.h"
#include "blocks/Blocks.h"
#include "mca/data/Database.h"
#include "util/ItemUtils.h"
#include "ICPE.h"

const float LuminatorBlockEntity::energyPerTick=0.25;

bool LuminatorBlockEntity::isEnergyReceiver(FacingEnum)const
{
	return true;
}
LuminatorBlockEntity::LuminatorBlockEntity(BlockPos const&pos):ElectricMachineBlockEntity(pos,3)
{
	isLit_=false;
}
void LuminatorBlockEntity::load(mca::CompoundTag const&tag)
{
	ElectricMachineBlockEntity::load(tag);
	
	isLit_=tag.getBool("isLit");
}
void LuminatorBlockEntity::save(mca::CompoundTag &tag)const
{
	ElectricMachineBlockEntity::save(tag);
	
	tag.putBool("isLit",(bool)isLit_);
}
void LuminatorBlockEntity::tick(Level&l,unsigned long long t)
{
	ElectricMachineBlockEntity::tick(l,t);
	
	if(canCharge())
	{
		if(ItemUtils::canCharge(*getSlot(0)))
		{
			unsigned int voltage=getItemVoltage(*getSlot(0));
			unsigned long energy=getItemEnergyLast(*getSlot(0));
			unsigned long energySholdMove;
			
			if(voltage>energy)
				energySholdMove=energy;
			else
				energySholdMove=voltage;
			
			if(getIVoltage()<energySholdMove)
				return explode();
			
			ItemUtils::setEnergy(*getSlot(0),ItemUtils::getEnergy(*getSlot(0))-energySholdMove);
			addEnergy(energySholdMove);
		}
		else if(canChargeWithDischargeable(*getSlot(0)))
		{
			unsigned int voltage=getItemVoltage(*getSlot(0));
			unsigned long energy=ItemUtils::getMaxEnergy(*getSlot(0));
			if(getIVoltage()<voltage)
				return explode();
		
			getSlot(0)->remove(1);
			addEnergy(energy);
		}
	}
	
	if(getEnergy()>=energyPerTick&&!isLit())
		setLit(true);
	else if(getEnergy()<energyPerTick&&isLit())
		setLit(false);
	
	if(isLit())
		costEnergyF(energyPerTick);
}
bool LuminatorBlockEntity::isLit()const
{
	return isLit_;
}
unsigned int LuminatorBlockEntity::getIVoltage()const
{
	return 32;
}
void LuminatorBlockEntity::setLit(bool b)
{
	isLit_=b;
	setBlockToLit(this,b);
}
bool LuminatorBlockEntity::canChargeWithDischargeable(ItemInstance const&item)
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
bool LuminatorBlockEntity::canPushInItem(ItemInstance const&i)
{
	return ItemUtils::isEnergyStorageItem(i)&&ItemUtils::getOVoltage(i)>0;
}
float LuminatorBlockEntity::getEnergyStorageProgress()const
{
	if(getEnergy()<=0)
		return 0.0F;
	return ((float)getEnergy())/((float)getEnergyStorage());
}
unsigned int LuminatorBlockEntity::getItemVoltage(ItemInstance const&i)const
{
	return ItemUtils::getOVoltage(i);
}
unsigned long LuminatorBlockEntity::getItemEnergyLast(ItemInstance const&i)const
{
	return ItemUtils::getEnergy(i);
}
bool LuminatorBlockEntity::canCharge()
{
	if(getEnergy()>=getEnergyStorage())
		return false;
	if(getSlot(0)&&!getSlot(0)->isNull())
	{
		if(ItemUtils::isEnergyStorageItem(*getSlot(0))&&ItemUtils::getOVoltage(*getSlot(0))>0)
		{
			unsigned long lastEnergy=getEnergyStorage()-getEnergy();
			if(lastEnergy>=((IC::Items*)Item::mItems[getSlot(0)->getId()])->getOVoltage())
				return true;
			if(getEnergy()<energyPerTick)
				return true;
			return false;
		}
	}
	return false;
}
unsigned long LuminatorBlockEntity::getEnergyStorageDefault()const
{
	return 10000;
}
void LuminatorBlockEntity::setBlockToLit(LuminatorBlockEntity*thiz,bool isLit_)
{
	/*BlockSource& region=thiz->getRegion();
	BlockPos const pos=thiz->pos;
	bool isLit__=thiz->isLit_;
	Energy eu=thiz->eu;
	std::vector<ItemInstance> items=thiz->slots;
	thiz->slots.clear();
	int data=region.getData(pos);
	if(data>0)
	{
		region.setBlockAndData(pos,FullBlock(isLit_?IC::Blocks::ID::mLuminatorActive:IC::Blocks::ID::mLuminator,data),3,0);
		((LuminatorBlockEntity*)region.getBlockEntity(pos))->eu=eu;
		((LuminatorBlockEntity*)region.getBlockEntity(pos))->slots=items;
		((LuminatorBlockEntity*)region.getBlockEntity(pos))->isLit_=isLit__;
	}
	else if(thiz->block!=region.getBlock(pos))
	{
		region.getLevel().destroyBlock(region,pos,true);
		ICPE::mBlockEntityManager.removeBlockEntity(region,pos);
	}*/
}
