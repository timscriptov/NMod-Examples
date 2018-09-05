#include "EnergyWeb.h"

#include "EnergySpreader.h"
#include "blocks/blockentity/ElectricMachineBlockEntity.h"
#include "blocks/blockentity/CableBlockEntity.h"
#include "util/Math.h"
#include "Energy.h"
#include "mcpe/level/BlockSource.h"
#include "blocks/Blocks.h"
#include "util/CableUtil.h"

EnergyWeb::EnergyWeb(BlockSource&s_,BlockPos const& pos):ps(&s_),startPos(pos)
{
	EnergySpreader es(s_,pos);
	es.calculate();
	energyLines=es.getEnergyLines();
}
EnergyWeb::EnergyWeb()
{
	startPos=BlockPos();
	ps=0;
}
std::vector<EnergyLine> EnergyWeb::getEnergyLines()const
{
	return energyLines;
}
void EnergyWeb::spreadEnergy(Energy&e,unsigned long long t)
{
	/*if(!ps)
		return;
	BlockSource&s=*ps;
	float energyCanPrivide=Math::min(((float)e.getEnergy())/((float)energyLines.size()),e.getVoltage());
	float energyShouldCost=0;
	
	for(EnergyLine line:energyLines)
	{
		if(energyCanPrivide<=0)
			return;
		std::vector<BlockPos>l=line.toVector();
		if(l.size()<2)
			continue;
		if(!(s.getBlockEntity(l[l.size()-1])&&s.getBlockEntity(l[l.size()-1])->isMachine()&&s.getBlockEntity(l[l.size()-1])->isElectricMachine()))
			continue;
		ElectricMachineBlockEntity*m = ((ElectricMachineBlockEntity*)s.getBlockEntity(l[l.size()-1]));
		if(!m)
			continue;
		float canAdd=Math::min(m->getEnergyStorage()-(m->getEnergy()),energyCanPrivide);
		float resistance=0;
		for(BlockPos const&pos:line.toVector())
		{
			if(s.getBlock(pos)==Block::mBlocks[IC::Blocks::ID::mCable])
			{
				CableBlockEntity*cableBlockEntity=(CableBlockEntity*)s.getBlockEntity(pos);
				resistance+=CableUtil::getResistance(s.getData(pos));
				if(cableBlockEntity)
				{
					cableBlockEntity->addVoltage(e.getVoltage());
					cableBlockEntity->addPower(e.getVoltage());
				}
			}
		}
		float finallyAdd=canAdd-resistance;
		
		if(m->getIVoltage()<e.getVoltage())
			m->explode();
		else
		{
			m->addEnergyF(finallyAdd);
			e.costEnergyF(finallyAdd);
		}
	}*/
}
BlockPos EnergyWeb::getStartPos()const
{
	return startPos;
}
void EnergyWeb::setStartPos(BlockPos const&pos_)
{
	startPos=pos_;
}
