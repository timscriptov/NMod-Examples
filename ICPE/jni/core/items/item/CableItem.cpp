#include "CableItem.h"

#include "mcpe/item/ItemInstance.h"
#include "mcpe/client/resources/I18n.h"

#include "blocks/Blocks.h"
#include "items/CableItemAux.h"
#include "util/CableUtil.h"

CableItem::CableItem(std::string const&name,short id):IC::Items(name,id)
{
	setCategory(CreativeItemCategory::ITEMS);
	setStackedByData(true);
}
bool CableItem::_useOn(ItemInstance&instance, Entity&ent, BlockPos pos, signed char side, float pixelx, float pixely, float pixelz)const
{
	ItemInstance item(IC::Blocks::ID::mCable,1,instance.getAuxValue());
	return Item::mItems[IC::Blocks::ID::mCable]->useOn(item,ent,pos.x,pos.y,pos.z,side,pixelx,pixely,pixelz);
}
TextureUVCoordinateSet const& CableItem::getIcon(int aux, int i, bool b) const
{
	((Item*)this)->setIcon("icpe_cable_item",aux);
	return Item::getIcon(aux,i,b);
}
std::string CableItem::buildDescriptionName(ItemInstance const&item) const
{
	switch(item.getAuxValue())
	{
	case (short)CableItemAux::TIN_0:
	default:
		return I18n::get("cable.tin_cable_0");
	case (short)CableItemAux::TIN_1:
		return I18n::get("cable.tin_cable_1");
	case (short)CableItemAux::IRON_0:
		return I18n::get("cable.iron_cable_0");
	case (short)CableItemAux::IRON_1:
		return I18n::get("cable.iron_cable_1");
	case (short)CableItemAux::IRON_2:
		return I18n::get("cable.iron_cable_2");
	case (short)CableItemAux::IRON_3:
		return I18n::get("cable.iron_cable_3");
	case (short)CableItemAux::GOLD_0:
		return I18n::get("cable.gold_cable_0");
	case (short)CableItemAux::GOLD_1:
		return I18n::get("cable.gold_cable_1");
	case (short)CableItemAux::GOLD_2:
		return I18n::get("cable.gold_cable_2");
	case (short)CableItemAux::COPPER_0:
		return I18n::get("cable.copper_cable_0");
	case (short)CableItemAux::COPPER_1:
		return I18n::get("cable.copper_cable_1");
	case (short)CableItemAux::DETECTOR:
	case (short)CableItemAux::DETECTOR_ACTIVE:
		return I18n::get("cable.detector_cable");
	case (short)CableItemAux::GLASS:
		return I18n::get("cable.glass_cable");
	case (short)CableItemAux::SPLITTER:
	case (short)CableItemAux::SPLITTER_ACTIVE:
		return I18n::get("cable.splitter_cable");
	}
	return "";
}
