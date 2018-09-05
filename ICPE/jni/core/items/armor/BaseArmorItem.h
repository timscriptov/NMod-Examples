#pragma once

#include "mcpe/item/ArmorItem.h"

class BaseArmorItem : public ArmorItem
{
private:
	std::string descriptionName;
	unsigned short repairItemID;
public:
	BaseArmorItem(int,std::string const&,std::string const&,int,int,ArmorItem::ArmorMaterial&,ArmorSlot,unsigned short);
public:
	virtual std::string buildDescriptionName(ItemInstance const&) const;
	virtual bool isValidRepairItem(ItemInstance const&, ItemInstance const&);
};
