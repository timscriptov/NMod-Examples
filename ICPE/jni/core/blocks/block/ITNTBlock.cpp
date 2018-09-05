#include "ITNTBlock.h"

#include "blocks/Blocks.h"

#include "mcpe/block/blocks/FireBlock.h"
#include "mcpe/client/resources/I18n.h"

ITNTBlock::ITNTBlock():TntBlock("te.itnt",IC::Blocks::ID::mITNT)
{
	setCategory(CreativeItemCategory::TOOLS);
	
	((FireBlock*)mFire)->setFlammable(BlockID(IC::Blocks::ID::mITNT),65,25);
}
std::string ITNTBlock::buildDescriptionName(unsigned char) const
{
	return I18n::get("te.itnt");
}
