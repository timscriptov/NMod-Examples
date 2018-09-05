#pragma once

#include "mcpe/block/Material/Material.h"

class ICMaterial
{
public:
	//static Material uuMatter;
public:
	static void initMaterials();
	static Material const& getUUMatterMaterial();
};
