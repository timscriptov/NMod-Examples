#include "FireGeneratorBlockEntity.h"

#include <stdlib.h>
#include <cmath>

#include "mcpe/item/ItemInstance.h"
#include "mcpe/blockentity/FurnaceBlockEntity.h"
#include "mcpe/recipe/FurnaceRecipes.h"

#include "items/Items.h"
#include "blocks/Blocks.h"
#include "mca/data/Database.h"
#include "util/ItemUtils.h"
#include "util/Math.h"

const float FireGeneratorBlockEntity::mSpeed=0.0075F;

FireGeneratorBlockEntity::FireGeneratorBlockEntity(BlockPos const&pos):ElectricMachineBlockEntity(pos,2)
{
	fireProgress=0;
	maxFireProgress=0;
	isLit_=false;
}
void FireGeneratorBlockEntity::load(mca::CompoundTag const&tag)
{
	ElectricMachineBlockEntity::load(tag);
	
	fireProgress=tag.getInt("fireProgress");
	maxFireProgress=tag.getInt("maxFireProgress");
	isLit_=tag.getBool("isLit");
}
void FireGeneratorBlockEntity::save(mca::CompoundTag &tag)const
{
	ElectricMachineBlockEntity::save(tag);
	
	tag.putInt("maxFireProgress",(int)maxFireProgress);
	tag.putInt("fireProgress",(int)fireProgress);
	tag.putBool("isLit",(bool)isLit_);
}
void FireGeneratorBlockEntity::tick(Level&l,unsigned long long t)
{
	ElectricMachineBlockEntity::tick(l,t);
	
	if(fireProgress>0)
		--fireProgress;
	else
		fireProgress=0;
	
	if(canStartNextFire())
	{
		maxFireProgress=fireProgress=getBurnDuration(getSlot(1));
		if(getSlot(1)->getId()!=325&&getSlot(1)->getAuxValue()!=10)
			getSlot(1)->remove(1);
		else
			getSlot(1)->aux=0;
	}
	if(fireProgress>0&&!isLit())
		setLit(true);
	else if(fireProgress<=0&&isLit())
		setLit(false);
	if(isLit())
		addEnergy(10);
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
	
	spreadEnergy(t);
}
bool FireGeneratorBlockEntity::isLit()const
{
	return isLit_;
}
void FireGeneratorBlockEntity::setLit(bool b)
{
	isLit_=b;
	//update();
}
bool FireGeneratorBlockEntity::canPushInItem(int s,ItemInstance const&i)
{
	if(getSlot(s)&&!getSlot(s)->isNull()&&getSlot(s)->getId()!=i.getId())
		return false;
	if(s==1&&getBurnDuration(&i)>0)
		return true;
	if(s==0&&ItemUtils::isEnergyStorageItem(i)&&ItemUtils::canCharge(i))
		return true;
	return false;
}
float FireGeneratorBlockEntity::getEnergyProgress()const
{
	return ((float)getEnergy())/((float)getEnergyStorage());
}
float FireGeneratorBlockEntity::getFireProgress()const
{
	if(fireProgress<=0||maxFireProgress<=0)
		return 0.0F;
	return ((float)fireProgress)/((float)maxFireProgress);
}
bool FireGeneratorBlockEntity::canStartNextFire()
{
	if(!fireProgress<=0)
		return false;
	if(!(getSlot(1)&&!getSlot(1)->isNull()&&getEnergy()<getEnergyStorage()))
		return false;
	if(getBurnDuration(getSlot(1))<=0)
		return false;
	return true;
}
unsigned long FireGeneratorBlockEntity::getEnergyStorageDefault()const
{
	return 4000;
}
bool FireGeneratorBlockEntity::isEnergyProvider(FacingEnum)const
{
	return true;
}
unsigned int FireGeneratorBlockEntity::getOVoltage()const
{
	return 10;
}
int FireGeneratorBlockEntity::getBurnDuration(ItemInstance const*item)const
{
	if(!item||item->isNull())
		return 0;
	int id=item->getId();
	int aux=item->getAuxValue();
	switch(id)
	{
	case 325:
		if(aux==10)
			return 2E3;
	break;
	case 173:
		return 16000;
	case 369:
		return 2400;
	case 263:
		return 1600;
	case 333:
		return 1200;
	case 158:
	case 5:
	case 17:
	case 162:
	case 85:
	case 107:
	case 134:
	case 135:
	case 136:
	case 163:
	case 164:
	case 53:
	case 72:
	case 58:
	case 96:
	case 47:
	case 54:
	case 146:
	case 151:
	case 178:
	case 99:
	case 100:
	case 25:
	case IC::Blocks::ID::mRubberWood:
		return 300;
	case 261:
	case 268:
	case 269:
	case 270:
	case 271:
	case 290:
	case 281:
	//case IC::Items::ID::mResin:
		return 200;
	case 6:
	case 280:
	case IC::Blocks::ID::mRubberSapling:
		return 100;
	}
	return 0;
}
