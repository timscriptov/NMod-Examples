#include "ElectricSourceBlock.h"

ElectricSourceBlock::ElectricSourceBlock(const std::string&name, int id, const Material&m):ElectricBlock(name,id,m)
{
	
}
bool ElectricSourceBlock::isElectricProvider(BlockSource&,BlockPos const&)const
{
	return true;
}
