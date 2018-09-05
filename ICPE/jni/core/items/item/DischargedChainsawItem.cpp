#include "DischargedChainsawItem.h"

#include <stdlib.h>

#include "mcpe/item/ItemInstance.h"
#include "mcpe/block/Block.h"
#include "mcpe/entity/player/Player.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/util/FullBlock.h"
#include "mcpe/util/Util.h"
#include "mcpe/client/resources/I18n.h"

DischargedChainsawItem::DischargedChainsawItem():EnergyStorageItem("chainsaw",ID::mDischargedChainsaw-0x100)
{
	setIcon("icpe_chainsaw",0);
	setCategory(CreativeItemCategory::TOOLS);
	setHandEquipped();
}
std::string DischargedChainsawItem::buildEffectDescriptionName(ItemInstance const&item) const
{
	return EnergyStorageItem::buildEffectDescriptionName(item)+"\n"+I18n::get("tooltip.mode",{I18n::get("tooltip.mode.silkTouch")});
}
std::string DischargedChainsawItem::getInteractText(Player const&) const
{
	return I18n::get("AdvMiner.gui.switch.mode");
}
bool DischargedChainsawItem::requiresInteract() const
{
	return true;
}
void DischargedChainsawItem::onInteract(ItemInstance&item)const
{
	item.item=mItems[ID::mDischargedChainsaw2];
}
float DischargedChainsawItem::getDestroySpeed(ItemInstance const&instance, Block const&block)const
{
	if(!hasEnergy(instance,50))
		return Item::getDestroySpeed(instance,block);
	float speed=0;
	speed=mSword_diamond->getDestroySpeed(instance,block)>speed?mSword_diamond->getDestroySpeed(instance,block):speed;
	speed=mShears->getDestroySpeed(instance,block)>speed?mShears->getDestroySpeed(instance,block):speed;
	speed=mHatchet_diamond->getDestroySpeed(instance,block)>speed?mHatchet_diamond->getDestroySpeed(instance,block):speed;
	return speed;
}
bool DischargedChainsawItem::canDestroySpecial(const Block&block) const
{
	bool canDestroy=false;
	return mSword_diamond->canDestroySpecial(block)||
	mHatchet_diamond->canDestroySpecial(block)||
	mShears->canDestroySpecial(block);
	return canDestroy;
}
void DischargedChainsawItem::mineBlock(ItemInstance&instance, BlockID id, int x,int y ,int z,Entity*e)const
{
	if(!hasEnergy(instance,50))
		return;
	mShears->mineBlock(instance,id,x,y,z,e);
	costEnergy(instance,50);
}
unsigned long DischargedChainsawItem::getMaxEnergy()const
{
	return 30000;
}
void DischargedChainsawItem::inventoryTick(ItemInstance&item, Level&, Entity&, int, bool)const
{
	if(hasEnergy(item,100))
		item.item=mItems[ID::mChainsaw];
}
unsigned int DischargedChainsawItem::getIVoltage()const
{
	return 15;
}
