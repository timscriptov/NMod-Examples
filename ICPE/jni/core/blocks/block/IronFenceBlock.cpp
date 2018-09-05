#include "IronFenceBlock.h"

#include "blocks/Blocks.h"
#include "mcpe/client/resources/I18n.h"

IronFenceBlock::IronFenceBlock():FenceBlock("fence.iron",IC::Blocks::ID::mIronFence,Material::getMaterial(MaterialType::METAL))
{
	init();
	setCategory(CreativeItemCategory::DECORATIONS);
	setSolid(false);
	setDestroyTime(3);
	setExplodeable(10);
}
std::string IronFenceBlock::buildDescriptionName(unsigned char) const
{
	return I18n::get("fence.iron");
}
