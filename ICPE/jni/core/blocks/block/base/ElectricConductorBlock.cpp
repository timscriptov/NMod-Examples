#include "ElectricConductorBlock.h"

ElectricConductorBlock::ElectricConductorBlock(const std::string&name, int id, const Material&m):ElectricBlock(name,id,m)
{
	
}
bool ElectricConductorBlock::isElectricConductor(BlockSource&,BlockPos const&)const
{
	return true;
}
