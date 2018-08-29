#include "ExtendsBlock.h"

ExtendsBlock::ExtendsBlock(std::string const&name,int id):Block(name,id,Material::getMaterial(MaterialType::DEVICE))
{
	setCategory(CreativeItemCategory::BLOCKS);
	setVisualShape(AABB(0.4375,0,0.4375,0.5625,1,0.5625));
	setLightEmission(1.0);
	setExplodeable(1E2);
	setDestroyTime(-1);
	setSolid(false);
}
