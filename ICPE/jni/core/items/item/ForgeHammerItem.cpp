#include "ForgeHammerItem.h"

#include "mcpe/entity/player/Player.h"

ForgeHammerItem::ForgeHammerItem():IC::Items("forge_hammer",IC::Items::ID::mForgeHammer-0x100)
{
	setIcon("icpe_forge_hammer",0);
	setMaxStackSize(70);
	setCategory(CreativeItemCategory::TOOLS);
	setHandEquipped();
}
void ForgeHammerItem::onCraftedBy(ItemInstance&item, Level&, Player&player)const
{
	
}
