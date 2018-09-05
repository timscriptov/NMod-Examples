#include "EnergySpreader.h"

#include "util/CableUtil.h"
#include "blocks/Blocks.h"
#include "blocks/blockentity/CableBlockEntity.h"
#include "mcpe/level/BlockSource.h"

EnergySpreader::EnergySpreader(BlockSource&bs,BlockPos const& pos_):s(bs),pos(pos_)
{
	
}
void EnergySpreader::calculate()
{
	_calculate(pos,EnergyLine(pos));
}
bool EnergySpreader::isReceiver(FacingEnum face,BlockPos const& pos2)
{
	return false;
	//return IC::Blocks::mICBlocks[s.getBlockID(pos2).id]&&IC::Blocks::mICBlocks[s.getBlockID(pos2).id]->isElectricReceiver(s,pos2,face)&&s.getBlockEntity(pos2)&&s.getBlockEntity(pos2)->isElectricMachine();
}
bool EnergySpreader::isConductor(BlockPos const &pos1,BlockPos const &pos2)
{
	bool isCable1=s.getBlock(pos1)==Block::mBlocks[IC::Blocks::ID::mCable];
	bool isCable2=s.getBlock(pos2)==Block::mBlocks[IC::Blocks::ID::mCable];
	if(isCable1&&isCable2)
	{
		CableBlockEntity*be1=(CableBlockEntity*)s.getBlockEntity(pos1);
		CableBlockEntity*be2=(CableBlockEntity*)s.getBlockEntity(pos2);
		if(be1&&be2&&be1->getColor()==be2->getColor())
			return true;
		else
			return false;
	}
	else if(isCable2)
		return true;
	return false;
}
bool EnergySpreader::isConductor(BlockPos const&pos)
{
	return s.getBlock(pos)==Block::mBlocks[IC::Blocks::ID::mCable];
}
bool EnergySpreader::isProvider(FacingEnum face,BlockPos const&pos)
{
	return IC::Blocks::mICBlocks[s.getBlockID(pos).id]&&((IC::Blocks*)s.getBlock(pos))->isElectricProvider(s,pos,face);
}
void EnergySpreader::newEnergyLine(EnergyLine line,BlockPos const&pos)
{
	line.addNew(pos);
	for(EnergyLine&l:lines)
	{
		if(l.getStart().x==line.getStart().x&&l.getStart().y==line.getStart().y&&l.getStart().z==line.getStart().z&&l.getEnd().x==line.getEnd().x&&l.getEnd().y==line.getEnd().y&&l.getEnd().z==line.getEnd().z)
		{
			if(l.toVector().size()>line.toVector().size())
			{
				l=line;
			}
			return;
		}
	}
	lines.push_back(line);
}
void EnergySpreader::_calculate(BlockPos const& pos,EnergyLine line)
{
	if(isConductor(pos)||isProvider(FacingEnum::UP,pos))
	{
		if(isReceiver(FacingEnum::DOWN,BlockPos(pos.x,pos.y+1,pos.z))&&!line.hasPosInList(BlockPos(pos.x,pos.y+1,pos.z)))
		{
			newEnergyLine(line,BlockPos(pos.x,pos.y+1,pos.z));
		}
		else if(isConductor(pos,BlockPos(pos.x,pos.y+1,pos.z))&&!line.hasPosInList(BlockPos(pos.x,pos.y+1,pos.z)))
		{
			addAndCalculate(BlockPos(pos.x,pos.y+1,pos.z),line);
		}
	}
	/////////////////////////////////////////////////
	if(isConductor(pos)||isProvider(FacingEnum::DOWN,pos))
	{
		if(isReceiver(FacingEnum::UP,BlockPos(pos.x,pos.y-1,pos.z))&&!line.hasPosInList(BlockPos(pos.x,pos.y-1,pos.z)))
		{
			newEnergyLine(line,BlockPos(pos.x,pos.y-1,pos.z));
		}
		else if(isConductor(pos,BlockPos(pos.x,pos.y-1,pos.z))&&!line.hasPosInList(BlockPos(pos.x,pos.y-1,pos.z)))
		{
			addAndCalculate(BlockPos(pos.x,pos.y-1,pos.z),line);
		}
	}
	/////////////////////////////////////////////////
	if(isConductor(pos)||isProvider(FacingEnum::EAST,pos))
	{
		if(isReceiver(FacingEnum::WEST,BlockPos(pos.x+1,pos.y,pos.z))&&!line.hasPosInList(BlockPos(pos.x+1,pos.y,pos.z)))
		{
			newEnergyLine(line,BlockPos(pos.x+1,pos.y,pos.z));
		}
		else if(isConductor(pos,BlockPos(pos.x+1,pos.y,pos.z))&&!line.hasPosInList(BlockPos(pos.x+1,pos.y,pos.z)))
		{
			addAndCalculate(BlockPos(pos.x+1,pos.y,pos.z),line);
		}
	}
	/////////////////////////////////////////////////
	if(isConductor(pos)||isProvider(FacingEnum::WEST,pos))
	{
		if(isReceiver(FacingEnum::EAST,BlockPos(pos.x-1,pos.y,pos.z))&&!line.hasPosInList(BlockPos(pos.x-1,pos.y,pos.z)))
		{
			newEnergyLine(line,BlockPos(pos.x-1,pos.y,pos.z));
		}
		else if(isConductor(pos,BlockPos(pos.x-1,pos.y,pos.z))&&!line.hasPosInList(BlockPos(pos.x-1,pos.y,pos.z)))
		{
			addAndCalculate(BlockPos(pos.x-1,pos.y,pos.z),line);
		}
	}
	/////////////////////////////////////////////////
	if(isConductor(pos)||isProvider(FacingEnum::SOUTH,pos))
	{
		if(isReceiver(FacingEnum::NORTH,BlockPos(pos.x,pos.y,pos.z+1))&&!line.hasPosInList(BlockPos(pos.x,pos.y,pos.z+1)))
		{
			newEnergyLine(line,BlockPos(pos.x,pos.y,pos.z+1));
		}
		else if(isConductor(pos,BlockPos(pos.x,pos.y,pos.z+1))&&!line.hasPosInList(BlockPos(pos.x,pos.y,pos.z+1)))
		{
			addAndCalculate(BlockPos(pos.x,pos.y,pos.z+1),line);
		}
	}
	/////////////////////////////////////////////////
	if(isConductor(pos)||isProvider(FacingEnum::NORTH,pos))
	{
		if(isReceiver(FacingEnum::SOUTH,BlockPos(pos.x,pos.y,pos.z-1))&&!line.hasPosInList(BlockPos(pos.x,pos.y,pos.z-1)))
		{
			newEnergyLine(line,BlockPos(pos.x,pos.y,pos.z-1));
		}
		else if(isConductor(pos,BlockPos(pos.x,pos.y,pos.z-1))&&!line.hasPosInList(BlockPos(pos.x,pos.y,pos.z-1)))
		{
			addAndCalculate(BlockPos(pos.x,pos.y,pos.z-1),line);
		}
	}
	/////////////////////////////////////////////////
}
void EnergySpreader::addAndCalculate(BlockPos const&pos,EnergyLine line)
{
	line.addNew(pos);
	_calculate(pos,line);
}
std::vector<EnergyLine> EnergySpreader::getEnergyLines()const
{
	return lines;
}
