#include "UUMatterStillBlock.h"

#include "blocks/Blocks.h"

UUMatterStillBlock::UUMatterStillBlock():LiquidBlockStatic("uu_matter",IC::Blocks::ID::mUUMatterStill,BlockID(IC::Blocks::ID::mUUMatterFlow),Material::getMaterial(MaterialType::WATER))
{
	setCategory(CreativeItemCategory::BLOCKS);
}
