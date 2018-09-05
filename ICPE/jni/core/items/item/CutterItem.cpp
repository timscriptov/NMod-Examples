#include "CutterItem.h"

#include "mcpe/entity/player/Player.h"

CutterItem::CutterItem():IC::Items("cutter",IC::Items::ID::mCutter-0x100)
{
	setIcon("icpe_cutter",0);
	setMaxStackSize(70);
	setCategory(CreativeItemCategory::TOOLS);
	setHandEquipped();
}
void CutterItem::onCraftedBy(ItemInstance&item, Level&, Player&player)const
{
	
}
