#pragma once

#include <string>
#include "mcpe/item/ArmorItem.h"

class ArmorDefine
{
public:
	static Item* defineArmor(int,std::string const&,std::string const&,int,std::string const&,int,ArmorItem::ArmorMaterial&,ArmorSlot,unsigned short);
};
