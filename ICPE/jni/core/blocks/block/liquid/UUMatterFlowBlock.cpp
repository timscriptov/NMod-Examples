#include "UUMatterFlowBlock.h"

#include "blocks/Blocks.h"

UUMatterFlowBlock::UUMatterFlowBlock():LiquidBlockDynamic("uu_matter",IC::Blocks::ID::mUUMatterFlow,Material::getMaterial(MaterialType::WATER))
{
	
}
