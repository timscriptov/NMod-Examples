#include "EnergyLine.h"

EnergyLine::EnergyLine(BlockPos const& pos)
{
	line.push_back(pos);
}
std::vector<BlockPos> EnergyLine::toVector()const
{
	return line;
}
EnergyLine EnergyLine::clone()const
{
	EnergyLine newl;
	newl.line=line;
	return newl;
}
bool EnergyLine::hasPosInList(BlockPos const& pos)
{
	for(BlockPos p:line)
	{
		if(p.x==pos.x&&p.y==pos.y&&pos.z==p.z)
			return true;
	}
	return false;
}
void EnergyLine::addNew(BlockPos const& pos)
{
	line.push_back(pos);
}
BlockPos EnergyLine::getStart()const
{
	return line[0];
}
BlockPos EnergyLine::getEnd()const
{
	return line[line.size()-1];
}
