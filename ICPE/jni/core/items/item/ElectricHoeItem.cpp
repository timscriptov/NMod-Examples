#include "ElectricHoeItem.h"

#include "mcpe/item/ItemInstance.h"
#include "mcpe/block/Block.h"
#include "mcpe/entity/player/Player.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/util/FullBlock.h"
#include "mcpe/util/Util.h"
#include "mcpe/client/resources/I18n.h"

ElectricHoeItem::ElectricHoeItem():EnergyStorageItem("electric_hoe",IC::Items::ID::mElectricHoe-0x100)
{
	setIcon("icpe_electric_hoe",0);
	setMaxStackSize(1);
	setCategory(CreativeItemCategory::TOOLS);
	setHandEquipped();
}
bool ElectricHoeItem::_useOn(ItemInstance&instance, Entity&p, BlockPos pos, signed char side, float px, float py, float pz)const
{
	if(!hasEnergy(instance,50))
		return false;
	mHoe_iron->_useOn(instance,p,pos,side,px,py,pz);
	costEnergy(instance,50);
	return false;
}
unsigned long ElectricHoeItem::getMaxEnergy()const
{
	return 10000;
}
unsigned int ElectricHoeItem::getIVoltage()const
{
	return 5;
}
