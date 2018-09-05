#include "CableBlockEntity.h"

#include "mca/data/tag/CompoundTag.h"
#include "util/CableUtil.h"
#include "util/Math.h"
#include "mcpe/level/Level.h"
#include "mcpe/level/BlockSource.h"
#include "ICPE.h"

CableBlockEntity::CableBlockEntity(BlockPos const&pos):ICBlockEntity(pos)
{
	colorType=15;
	lastTick=0;
	power=0;
	voltage=0;
	lastPower=0;
	lastVoltage=0;
	shouldUpdateNeighbors=false;
}
bool CableBlockEntity::isEnergyConductor()const
{
	return true;
}
void CableBlockEntity::tick(BlockSource&s)
{
	CBlockEntity::tick(s);
	
	if(shouldUpdateNeighbors)
	{
		updateTessellator(s);
		shouldUpdateNeighbors=false;
	}
	/*if(lastTick!=t)
	{
		if(voltage>CableUtil::getMaxVoltage(getRegion().getData(pos)))
		{
			getRegion().removeBlock(pos);
			return;
			//l.addParticle
		}
		lastPower=power;
		lastVoltage=voltage;
		lastTick=t;
		power=0;
		voltage=0;
	}*/
}
void CableBlockEntity::addVoltage(unsigned int v)
{
	voltage=Math::max(v,voltage);
}
void CableBlockEntity::addPower(unsigned long p)
{
	power+=p;
}
void CableBlockEntity::load(mca::CompoundTag const&tag)
{
	ICBlockEntity::load(tag);
	
	colorType=(unsigned short)tag.getUshort("colorType",15);
}
void CableBlockEntity::save(mca::CompoundTag&tag)const
{
	ICBlockEntity::save(tag);
	
	tag.putUshort("colorType",(unsigned short)colorType);
}
unsigned char CableBlockEntity::getColor()const
{
	return colorType;
}
void CableBlockEntity::setColor(unsigned char c)
{
	colorType=c;
	shouldUpdateNeighbors=true;
}
unsigned char CableBlockEntity::getTextureAux(unsigned char aux)const
{
	return CableUtil::dye(aux,getColor());
}
Energy CableBlockEntity::getEnergyConducted()const
{
	return Energy(lastPower,0,lastVoltage);
}
