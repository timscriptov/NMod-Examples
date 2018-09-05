#include "SolarGeneratorBlockEntity.h"

#include "mcpe/level/Weather.h"
#include "mcpe/level/Dimension.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/level/Level.h"
#include "mcpe/block/Block.h"

#include "mca/data/Database.h"
#include "items/Items.h"
#include "util/Math.h"
#include "util/ItemUtils.h"

SolarGeneratorBlockEntity::SolarGeneratorBlockEntity(BlockPos const&pos):ElectricMachineBlockEntity(pos,1)
{
	progress=0.0F;
	lastSpeed=0.0F;
}
void SolarGeneratorBlockEntity::load(mca::CompoundTag const&tag)
{
	ElectricMachineBlockEntity::load(tag);
	
	progress=tag.getFloat("solarProgress");
}
void SolarGeneratorBlockEntity::save(mca::CompoundTag&tag)const
{
	ElectricMachineBlockEntity::save(tag);
	
	tag.putFloat("solarProgress",progress);
}
bool SolarGeneratorBlockEntity::isEnergyProvider(FacingEnum face)const
{
	return true;
}
void SolarGeneratorBlockEntity::tick(Level&lv,unsigned long long t)
{
	ElectricMachineBlockEntity::tick(lv,t);
	
	setVoltage(getNowOutVoltage());
	progress+=getNowEUEveryTick(t);
	
	if(progress>=1.0F)
	{
		unsigned long energVar=(unsigned long)progress;
		addEnergy(energVar);
		progress-=(float)energVar;
	}
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
unsigned int SolarGeneratorBlockEntity::getNowOutVoltage()const
{
	return 1;
}
float SolarGeneratorBlockEntity::getNowEUEveryTick(unsigned long long t)
{
	/*if(t%20!=0)
		return lastSpeed;
	if(getRegion().getDimensionId()!=DimensionId::OVERWORLD)
		return lastSpeed=0.0F;
	int yPos=pos.y+1;
	int noSolidCount=0;
	float ret=1.0F;
	int time=getRegion().getLevel().getTime()%24000;
	bool isDay=time>=0&&time<=12000;
	for(;yPos<256;++yPos)
	{
		Block const* block=getRegion().getBlock(pos.x,yPos,pos.z);
		if(block->isSolid())
			return lastSpeed=0.00001F;
		if(block!=Block::mAir&&!block->isSolid())
			++noSolidCount;
	}
	ret-=(noSolidCount*0.05);
	
	if(!isDay||getRegion().getDimension()->getWeather()->isLightning())
		ret-=0.99;
	if(getRegion().getDimension()->getWeather()->isRaining()||getRegion().getDimension()->getWeather()->isRainingAt(getRegion(),{pos.x,pos.y+1,pos.z})||getRegion().getDimension()->getWeather()->isSnowingAt(getRegion(),{pos.x,pos.y+1,pos.z}))
		ret-=0.98;
	if(ret>=1.0F)
		return lastSpeed=1.0F;
	if(ret>=0.0F)
		return lastSpeed=ret;*/
	return lastSpeed=0.0F;
}
unsigned long SolarGeneratorBlockEntity::getEnergyStorageDefault()const
{
	return 1;
}
bool SolarGeneratorBlockEntity::isActive()const
{
	if(lastSpeed>=0.75)
		return true;
	return false;
}
bool SolarGeneratorBlockEntity::canPushInItem(ItemInstance const&item)
{
	return ItemUtils::isEnergyStorageItem(item);
}
