#pragma once

#include "blocks/Blocks.h"

class ResourcesBlock : public IC::Blocks
{
public:
	ResourcesBlock();
public:
	virtual bool isAnyAuxValueInRecipe()const;
	virtual std::string buildDescriptionName(unsigned char) const;
	virtual int getSpawnResourcesAuxValue(unsigned char) const;
};
