#include "IronFurnaceBlockEntity.h"

#include <stdlib.h>
#include <cmath>

#include "mcpe/item/ItemInstance.h"
#include "mcpe/blockentity/FurnaceBlockEntity.h"
#include "mcpe/recipe/FurnaceRecipes.h"

#include "items/Items.h"
#include "blocks/Blocks.h"
#include "mca/data/Database.h"

const float IronFurnaceBlockEntity::mSpeed=0.0075F;

IronFurnaceBlockEntity::IronFurnaceBlockEntity(BlockPos const&pos):ICMachineBlockEntity(pos,3)
{
	fireProgress=0;
	maxFireProgress=0;
	burnProgress=0.0F;
	isLit_=false;
}
void IronFurnaceBlockEntity::load(mca::CompoundTag const&tag)
{
	ICMachineBlockEntity::load(tag);
	
	fireProgress=tag.getInt("fireProgress");
	maxFireProgress=tag.getInt("maxFireProgress");
	burnProgress=tag.getFloat("burnProgress");
	isLit_=tag.getBool("isLit");
}
void IronFurnaceBlockEntity::save(mca::CompoundTag &tag)const
{
	ICMachineBlockEntity::save(tag);
	
	tag.putInt("maxFireProgress",(int)maxFireProgress);
	tag.putInt("fireProgress",(int)fireProgress);
	tag.putFloat("burnProgress",(float)burnProgress);
	tag.putBool("isLit",(bool)isLit_);
}
void IronFurnaceBlockEntity::tick(Level&,unsigned long long)
{
	if(burnProgress>=1.0F)
	{
		if(!getSlot(0)||getSlot(0)->isNull())
			goto burnEnd;
		ItemInstance item=FurnaceRecipes::getInstance()->getResult(*getSlot(0));
		if(item.isNull())
			goto burnEnd;
		if(!getSlot(2)||getSlot(2)->isNull())
			setSlot(2,&item);
		else
			++getSlot(2)->count;
		if(getSlot(1)&&!getSlot(1)->isNull()&&getSlot(1)->getId()==322&&getSlot(1)->getAuxValue()==0&&getSlot(0)->getId()==19&&getSlot(0)->getAuxValue()==1)
			getSlot(1)->aux=8;
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
}
bool IronFurnaceBlockEntity::isLit()const
{
	return isLit_;
}
void IronFurnaceBlockEntity::setLit(bool b)
{
	isLit_=b;
	//update();
}
bool IronFurnaceBlockEntity::canPushInItem(int s,ItemInstance const&i)
{
	if(getSlot(s)&&!getSlot(s)->isNull()&&getSlot(s)->getId()!=i.getId())
		return false;
	if(s==1&&getBurnDuration(&i)>0)
		return true;
	if(s==0)
		return true;
	return false;
}
float IronFurnaceBlockEntity::getBurnProgress()const
{
	if(burnProgress>=0.0F)
		return burnProgress;
	return 0.0F;
}
float IronFurnaceBlockEntity::getFireProgress()const
{
	if(fireProgress<=0||maxFireProgress<=0)
		return 0.0F;
	return ((float)fireProgress)/((float)maxFireProgress);
}
bool IronFurnaceBlockEntity::canBurn()
{
	if(fireProgress<=0)
		return false;
	if(!getSlot(0)||getSlot(0)->isNull())
		return false;
	if(FurnaceRecipes::mInstance->isFurnaceItem(*getSlot(0)))
	{
		if(getSlot(2)&&!getSlot(2)->isNull())
		{
			if(FurnaceRecipes::getInstance()->getResult(*getSlot(0)).sameItemAndAux(*getSlot(2))&&!getSlot(2)->isFullStack())
				return true;
			return false;
		}
		else
			return true;
	}
	return false;
}
bool IronFurnaceBlockEntity::canStartNextFire()
{
	if(!fireProgress<=0)
		return false;
	if(!(getSlot(0)&&getSlot(1)&&!getSlot(0)->isNull()&&!getSlot(1)->isNull()))
		return false;
	if(!FurnaceRecipes::getInstance()->isFurnaceItem(*getSlot(0)))
		return false;
	if(getBurnDuration(getSlot(1))<=0)
		return false;
	
	if(getSlot(2)&&!getSlot(2)->isNull())
	{
		if(FurnaceRecipes::getInstance()->getResult(*getSlot(0)).sameItemAndAux(*getSlot(2))&&!getSlot(2)->isFullStack())
			return true;
		return false;
	}
	return true;
}
int IronFurnaceBlockEntity::getBurnDuration(ItemInstance const*item)const
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
