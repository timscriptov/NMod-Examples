#include "ElectricBlock.h"

ElectricBlock::ElectricBlock(const std::string&name, int id, const Material&m):IC::Blocks(name,id,m)
{
	
}
bool ElectricBlock::isElectricBlock(BlockSource&,BlockPos const&)const
{
	return true;
}
