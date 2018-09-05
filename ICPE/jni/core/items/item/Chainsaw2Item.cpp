#include "Chainsaw2Item.h"

#include <stdlib.h>

#include "mcpe/item/ItemInstance.h"
#include "mcpe/block/Block.h"
#include "mcpe/entity/player/Player.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/util/FullBlock.h"
#include "mcpe/util/Util.h"
#include "mcpe/client/resources/I18n.h"
#include "util/sound/SoundManager.h"
#include "ICPE.h"

Chainsaw2Item::Chainsaw2Item():EnergyStorageItem("chainsaw",ID::mChainsaw2-0x100)
{
	setIcon("icpe_chainsaw",0);
	setCategory(CreativeItemCategory::TOOLS);
	setHandEquipped();
}
std::string Chainsaw2Item::buildEffectDescriptionName(ItemInstance const&item) const
{
	return EnergyStorageItem::buildEffectDescriptionName(item)+"\n"+I18n::get("tooltip.mode",{I18n::get("tooltip.mode.noShear")});
}
std::string Chainsaw2Item::getInteractText(Player const&) const
{
	return I18n::get("AdvMiner.gui.switch.mode");
}
bool Chainsaw2Item::requiresInteract() const
{
	return true;
}
void Chainsaw2Item::onInteract(ItemInstance&item)const
{
	item.item=mItems[ID::mChainsaw];
}
float Chainsaw2Item::getDestroySpeed(ItemInstance const&instance, Block const&block)const
{
	if(!hasEnergy(instance,50))
		return Item::getDestroySpeed(instance,block);
	float speed=0;
	speed=mSword_diamond->getDestroySpeed(instance,block)>speed?mSword_diamond->getDestroySpeed(instance,block):speed;
	speed=mHatchet_diamond->getDestroySpeed(instance,block)>speed?mHatchet_diamond->getDestroySpeed(instance,block):speed;
	return speed;
}
bool Chainsaw2Item::canDestroySpecial(const Block&block) const
{
	return mSword_diamond->canDestroySpecial(block)||
	mHatchet_diamond->canDestroySpecial(block);
}
void Chainsaw2Item::mineBlock(ItemInstance&instance, BlockID, int x, int y, int z, Entity*e)const
{
	if(!hasEnergy(instance,50))
		return;
	costEnergy(instance,50);
	ICPE::soundManager.playSound(Vec3(x,y,z),"Tools/Chainsaw/ChainsawUseOne.ogg");
}
void Chainsaw2Item::hurtEnemy(ItemInstance&instance, Mob*, Mob*m)const
{
	if(!hasEnergy(instance,100))
		return;
	costEnergy(instance,100);
	//if(m)
	//	ICPE::soundManager.playSound("Tools/Chainsaw/ChainsawUseOne.ogg");
}
int Chainsaw2Item::getAttackDamage()const
{
	return mSword_diamond->getAttackDamage();
}
unsigned long Chainsaw2Item::getMaxEnergy()const
{
	return 30000;
}
void Chainsaw2Item::inventoryTick(ItemInstance&item, Level&, Entity&e, int, bool)const
{
	if(!hasEnergy(item,100))
		item.item=mItems[ID::mDischargedChainsaw2];
}
unsigned int Chainsaw2Item::getIVoltage()const
{
	return 15;
}
std::string Chainsaw2Item::getLoopingSound(ItemInstance&)const
{
	return "Tools/Chainsaw/ChainsawIdle.ogg";
}
