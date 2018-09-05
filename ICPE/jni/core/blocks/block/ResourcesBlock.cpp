#include "ResourcesBlock.h"

#include "mcpe/client/resources/I18n.h"

ResourcesBlock::ResourcesBlock():IC::Blocks("resources",ID::mResources,Material::getMaterial(MaterialType::STONE))
{
	init();
	setCategory(CreativeItemCategory::DECORATIONS);
	setSolid(true);
	setDestroyTime(3);
	setExplodeable(10);
}
bool ResourcesBlock::isAnyAuxValueInRecipe()const
{
	return false;
}
int ResourcesBlock::getSpawnResourcesAuxValue(unsigned char aux) const
{
	return aux;
}
std::string ResourcesBlock::buildDescriptionName(unsigned char aux) const
{
	switch(aux)
	{
	case 0:
	default:
		return I18n::get("resource.tin_block");
	case 1:
		return I18n::get("resource.steel_block");
	case 2:
		return I18n::get("resource.copper_block");
	case 3:
		return I18n::get("resource.lead_block");
	case 4:
		return I18n::get("resource.machine");
	case 5:
		return I18n::get("resource.advanced_machine");
	case 6:
		return I18n::get("resource.bronze_block");
	case 7:
		return I18n::get("resource.uranium_block");
	case 8:
		return I18n::get("resource.tin_ore");
	case 9:
		return I18n::get("resource.copper_ore");
	case 10:
		return I18n::get("resource.lead_ore");
	case 11:
		return I18n::get("resource.uranium_ore");
	case 12:
		return I18n::get("resource.basalt");
	}
}
