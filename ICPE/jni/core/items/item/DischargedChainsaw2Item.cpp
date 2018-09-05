#include "DischargedChainsaw2Item.h"

#include <stdlib.h>

#include "mcpe/item/ItemInstance.h"
#include "mcpe/block/Block.h"
#include "mcpe/entity/player/Player.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/util/FullBlock.h"
#include "mcpe/util/Util.h"
#include "mcpe/client/resources/I18n.h"

DischargedChainsaw2Item::DischargedChainsaw2Item():EnergyStorageItem("chainsaw",ID::mDischargedChainsaw2-0x100)
{
	setIcon("icpe_chainsaw",0);
	setCategory(CreativeItemCategory::TOOLS);
	setHandEquipped();
}
std::string DischargedChainsaw2Item::buildEffectDescriptionName(ItemInstance const&item) const
{
	return EnergyStorageItem::buildEffectDescriptionName(item)+"\n"+I18n::get("tooltip.mode",{I18n::get("tooltip.mode.noShear")});
}
std::string DischargedChainsaw2Item::getInteractText(Player const&) const
{
	return I18n::get("AdvMiner.gui.switch.mode");
}
bool DischargedChainsaw2Item::requiresInteract() const
{
	return true;
}
void DischargedChainsaw2Item::onInteract(ItemInstance&item)const
{
	item.item=mItems[ID::mDischargedChainsaw];
}
float DischargedChainsaw2Item::getDestroySpeed(ItemInstance const&instance, Block const&block)const
{
	if(!hasEnergy(instance,50))
		return Item::getDestroySpeed(instance,block);
	float speed=0;
	speed=mSword_diamond->getDestroySpeed(instance,block)>speed?mSword_diamond->getDestroySpeed(instance,block):speed;
	speed=mHatchet_diamond->getDestroySpeed(instance,block)>speed?mHatchet_diamond->getDestroySpeed(instance,block):speed;
	return speed;
}
bool DischargedChainsaw2Item::canDestroySpecial(const Block&block) const
{
	bool canDestroy=false;
	return mSword_diamond->canDestroySpecial(block)||
	mHatchet_diamond->canDestroySpecial(block);
	return canDestroy;
}
void DischargedChainsaw2Item::mineBlock(ItemInstance&instance, BlockID, int, int, int, Entity*e)const
{
	if(!hasEnergy(instance,50))
		return;
	costEnergy(instance,50);
}
unsigned long DischargedChainsaw2Item::getMaxEnergy()const
{
	return 30000;
}
void DischargedChainsaw2Item::inventoryTick(ItemInstance&item, Level&, Entity&, int, bool)const
{
	if(hasEnergy(item,100))
		item.item=mItems[ID::mChainsaw2];
}
unsigned int DischargedChainsaw2Item::getIVoltage()const
{
	return 15;
}
