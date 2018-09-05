#include "ChainsawItem.h"

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

ChainsawItem::ChainsawItem():EnergyStorageItem("chainsaw",ID::mChainsaw-0x100)
{
	setIcon("icpe_chainsaw",0);
	setCategory(CreativeItemCategory::TOOLS);
	setHandEquipped();
}
std::string ChainsawItem::buildEffectDescriptionName(ItemInstance const&item) const
{
	return EnergyStorageItem::buildEffectDescriptionName(item)+"\n"+I18n::get("tooltip.mode",{I18n::get("tooltip.mode.silkTouch")});
}
std::string ChainsawItem::getInteractText(Player const&) const
{
	return I18n::get("AdvMiner.gui.switch.mode");
}
bool ChainsawItem::requiresInteract() const
{
	return true;
}
void ChainsawItem::onInteract(ItemInstance&item)const
{
	item.item=mItems[ID::mChainsaw2];
}
float ChainsawItem::getDestroySpeed(ItemInstance const&instance, Block const&block)const
{
	if(!hasEnergy(instance,50))
		return Item::getDestroySpeed(instance,block);
	float speed=0;
	speed=mSword_diamond->getDestroySpeed(instance,block)>speed?mSword_diamond->getDestroySpeed(instance,block):speed;
	speed=mShears->getDestroySpeed(instance,block)>speed?mShears->getDestroySpeed(instance,block):speed;
	speed=mHatchet_diamond->getDestroySpeed(instance,block)>speed?mHatchet_diamond->getDestroySpeed(instance,block):speed;
	return speed;
}
bool ChainsawItem::canDestroySpecial(const Block&block) const
{
	return mSword_diamond->canDestroySpecial(block)||
	mHatchet_diamond->canDestroySpecial(block)||
	mShears->canDestroySpecial(block);
}
void ChainsawItem::mineBlock(ItemInstance&instance, BlockID id, int x,int y ,int z,Entity*e)const
{
	if(!hasEnergy(instance,50))
		return;
	mShears->mineBlock(instance,id,x,y,z,e);
	costEnergy(instance,50);
	ICPE::soundManager.playSound(Vec3(x,y,z),"Tools/Chainsaw/ChainsawUseOne.ogg");
}
void ChainsawItem::hurtEnemy(ItemInstance&instance, Mob*, Mob*m)const
{
	if(!hasEnergy(instance,100))
		return;
	costEnergy(instance,100);
	//if(m)
	//	ICPE::soundManager.playSound("Tools/Chainsaw/ChainsawUseOne.ogg");
}
int ChainsawItem::getAttackDamage()const
{
	return mSword_diamond->getAttackDamage();
}
unsigned long ChainsawItem::getMaxEnergy()const
{
	return 30000;
}
void ChainsawItem::inventoryTick(ItemInstance&item, Level&, Entity&e, int, bool)const
{
	if(!hasEnergy(item,100))
		item.item=mItems[ID::mDischargedChainsaw];
}
unsigned int ChainsawItem::getIVoltage()const
{
	return 15;
}
std::string ChainsawItem::getLoopingSound(ItemInstance&)const
{
	return "Tools/Chainsaw/ChainSawIgle.ogg";
}
