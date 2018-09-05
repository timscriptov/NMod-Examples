#include "ArmorDefine.h"

#include "BaseArmorItem.h"

Item* ArmorDefine::defineArmor(int itemID,std::string const&itemName,std::string const&itemIcon,int iconIndex,std::string const&texture,int damage,ArmorItem::ArmorMaterial&material,ArmorSlot slot,unsigned short reid)
{
	Item* itemNew = new BaseArmorItem(itemID,itemName,itemIcon,iconIndex,damage,material,slot,reid);
	//bl_setArmorTexture(itemID+0x100,texture);
	return itemNew;
}
