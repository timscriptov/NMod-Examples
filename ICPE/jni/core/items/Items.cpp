#include "Items.h"

#include "mcpe/item/BlockItem.h"
#include "mcpe/item/AuxDataBlockItem.h"
#include "mcpe/block/Block.h"
#include "mcpe/client/resources/I18n.h"

#include "blocks/Blocks.h"
#include "util/ItemUtils.h"
#include "armor/ArmorDefine.h"

#include "item/base/ICDefaultItem.h"
#include "item/battery/SingleUseBatteryItem.h"
#include "item/battery/ICRedstoneDustItem.h"
#include "item/battery/REBatteryItem.h"
#include "item/battery/ChargingREBatteryItem.h"
#include "item/CutterItem.h"
#include "item/TreeTapItem.h"
#include "item/CableItem.h"
#include "item/ForgeHammerItem.h"
#include "item/ElectricTreeTapItem.h"
#include "item/ElectricHoeItem.h"
#include "item/ChainsawItem.h"
#include "item/Chainsaw2Item.h"
#include "item/DischargedChainsawItem.h"
#include "item/DischargedChainsaw2Item.h"
#include "item/PainterItem.h"
#include "item/BronzeShovelItem.h"
#include "item/BronzeHoeItem.h"
#include "item/BronzeSwordItem.h"
#include "item/BronzePickAxeItem.h"
#include "item/BronzeAxeItem.h"
#include "item/WrenchItem.h"
#include "item/RotorItem.h"
#include "item/MeterItem.h"
#include "item/WindMeterItem.h"
#include "item/ElectricWrenchItem.h"
#include "item/ResItem.h"

IC::Items* IC::Items::mICItems[4096];
bool IC::Items::hasTeardown=true;

namespace IC
{
void Items::teardownICItems()
{
	hasTeardown=true;
}
void Items::initICAllItems()
{
	if(!hasTeardown)
		return;
	for(Items* & item : mICItems)
		item=0;
	initICItems();
	initICBlockItems();
}
void Items::addICCreativeItems()
{
	initICAllItems();
	
	Item::addCreativeItem(IC::Blocks::ID::mRubberSapling,0);
	Item::addCreativeItem(IC::Blocks::ID::mRubberWood,0);
	Item::addCreativeItem(IC::Blocks::ID::mRubberLeaves,0);
	addCreativeItemAuxData(IC::Blocks::ID::mResin,2);
	addCreativeItemAuxData(IC::Blocks::ID::mResources,13);
	Item::addCreativeItem(IC::Blocks::ID::mIronFence,0);
	addCreativeItemAuxData(IC::Blocks::ID::mCable,12);
	
	addCreativeItemAuxData(ID::mResources,179);
	addCreativeItemAuxData(ID::mCable,12);
	addCreativeItemAuxData(ID::mPainter,17);
}

void Items::initICItems()
{
	/*
	Item::mItems[331]=Item::mRedStone=new ICRedstoneDustItem();
	Item::mItems[ID::mHelmet_bronze]=ArmorDefine::defineArmor(ID::mHelmet_bronze-0x100,"bronze_helmet","icpe_bronze_helmet",0,"textures/models/armor/bronze_1.png",300,ArmorItem::IRON,ArmorSlot::HELMET,Items::ID::mBronzeIngot);
	Item::mItems[ID::mChestplate_bronze]=ArmorDefine::defineArmor(ID::mChestplate_bronze-0x100,"bronze_chestplate","icpe_bronze_chestplate",0,"textures/models/armor/bronze_1.png",300,ArmorItem::IRON,ArmorSlot::CHESTPLATE,Items::ID::mBronzeIngot);
	Item::mItems[ID::mLeggings_bronze]=ArmorDefine::defineArmor(ID::mLeggings_bronze-0x100,"bronze_leggings","icpe_bronze_leggings",0,"textures/models/armor/bronze_2.png",300,ArmorItem::IRON,ArmorSlot::LEGGINGS,Items::ID::mBronzeIngot);
	Item::mItems[ID::mBoots_bronze]=ArmorDefine::defineArmor(ID::mBoots_bronze-0x100,"bronze_boots","icpe_bronze_boots",0,"textures/models/armor/bronze_2.png",300,ArmorItem::IRON,ArmorSlot::BOOTS,Items::ID::mBronzeIngot);
	Item::mItems[ID::mIronRotor]=new RotorItem("rotor_iron",ID::mIronRotor-0x100,"icpe_iron_rotor",0,200);
	Item::mItems[ID::mSteelRotor]=new RotorItem("rotor_steel",ID::mSteelRotor-0x100,"icpe_steel_rotor",0,200);
	Item::mItems[ID::mWoodRotor]=new RotorItem("rotor_wood",ID::mWoodRotor-0x100,"icpe_wood_rotor",0,200);
	Item::mItems[ID::mCarbonRotor]=new RotorItem("rotor_carbon",ID::mCarbonRotor-0x100,"icpe_carbon_rotor",0,200);
	Item::mItems[ID::mSingleUseBattery]=new SingleUseBatteryItem();
	Item::mItems[ID::mChainsaw]=new ChainsawItem();
	Item::mItems[ID::mChainsaw2]=new Chainsaw2Item();
	Item::mItems[ID::mDischargedChainsaw2]=new DischargedChainsaw2Item();
	Item::mItems[ID::mDischargedChainsaw]=new DischargedChainsawItem();
	Item::mItems[ID::mElectricHoe]=new ElectricHoeItem();
	Item::mItems[ID::mElectricTreeTap]=new ElectricTreeTapItem();
	Item::mItems[ID::mForgeHammer]=new ForgeHammerItem();
	Item::mItems[ID::mTreeTap]=new TreeTapItem();
	Item::mItems[ID::mBronzeShovel]=new BronzeShovelItem();
	Item::mItems[ID::mBronzeHoe]=new BronzeHoeItem();
	Item::mItems[ID::mBronzeSword]=new BronzeSwordItem();
	Item::mItems[ID::mBronzePickAxe]=new BronzePickAxeItem();
	Item::mItems[ID::mBronzeAxe]=new BronzeAxeItem();
	Item::mItems[ID::mReBattery]=new REBatteryItem();
	Item::mItems[ID::mChargingReBattery]=new ChargingREBatteryItem();
	Item::mItems[ID::mCutter]=new CutterItem();
	Item::mItems[ID::mWrench]=new WrenchItem();
	Item::mItems[ID::mWindMeter]=new WindMeterItem();
	Item::mItems[ID::mElectricWrench]=new ElectricWrenchItem();
	Item::mItems[ID::mMeter]=new MeterItem();*/
	Item::mItems[ID::mCable]=new CableItem("cable",ID::mCable-0x100);
	Item::mItems[ID::mResources]=new ResItem();
	Item::mItems[ID::mPainter]=new PainterItem();
}
void Items::initICBlockItems()
{
	
	Item::mItems[IC::Blocks::ID::mResources]=new AuxDataBlockItem("",IC::Blocks::ID::mResources-0x100,Block::mBlocks[IC::Blocks::ID::mResources]);
	Item::mItems[IC::Blocks::ID::mIronFence]=new BlockItem("",IC::Blocks::ID::mIronFence-0x100);
	//Item::mItems[IC::Blocks::ID::mFurnace]=new AuxDataBlockItem("",IC::Blocks::ID::mFurnace-0x100,Block::mBlocks[IC::Blocks::ID::mFurnace]);
	Item::mItems[IC::Blocks::ID::mCable]=new AuxDataBlockItem("",IC::Blocks::ID::mCable-0x100,Block::mBlocks[IC::Blocks::ID::mCable]);
	Item::mItems[IC::Blocks::ID::mRubberLeaves]=new BlockItem("",IC::Blocks::ID::mRubberLeaves-0x100);
	Item::mItems[IC::Blocks::ID::mResin]=new AuxDataBlockItem("",IC::Blocks::ID::mResin-0x100,Block::mBlocks[IC::Blocks::ID::mResin]);
	Item::mItems[IC::Blocks::ID::mRubberWood]=new AuxDataBlockItem("",IC::Blocks::ID::mRubberWood-0x100,Block::mBlocks[IC::Blocks::ID::mRubberWood]);
	//Item::mItems[IC::Blocks::ID::mITNT]=new BlockItem("",IC::Blocks::ID::mITNT-0x100);
	//Item::mItems[IC::Blocks::ID::mLuminator]=new BlockItem("",IC::Blocks::ID::mLuminator-0x100);
	//Item::mItems[IC::Blocks::ID::mLuminatorActive]=new BlockItem("",IC::Blocks::ID::mLuminatorActive-0x100);
	//Item::mItems[IC::Blocks::ID::mUUMatterFlow]=new BlockItem("",IC::Blocks::ID::mUUMatterFlow-0x100);
	//Item::mItems[IC::Blocks::ID::mUUMatterStill]=new BlockItem("",IC::Blocks::ID::mUUMatterStill-0x100);
	Item::mItems[IC::Blocks::ID::mRubberSapling]=new BlockItem("",IC::Blocks::ID::mRubberSapling-0x100);
	//Item::mItems[IC::Blocks::ID::mGenerator1]=new AuxDataBlockItem("",IC::Blocks::ID::mGenerator1-0x100,Block::mBlocks[IC::Blocks::ID::mGenerator1]);
	//Item::mItems[IC::Blocks::ID::mMachine1]=new AuxDataBlockItem("",IC::Blocks::ID::mMachine1-0x100,Block::mBlocks[IC::Blocks::ID::mMachine1]);
	//Item::mItems[IC::Blocks::ID::mBatBox]=new AuxDataBlockItem("",IC::Blocks::ID::mBatBox-0x100,Block::mBlocks[IC::Blocks::ID::mBatBox]);
}
unsigned int Items::getIVoltage()const
{
	return 0;
}
unsigned int Items::getOVoltage()const
{
	return 0;
}
Items::Items(std::string const&name,short id):Item(name,id)
{
	mICItems[id+0x100]=this;
	descriptionName = name;
	//mItemLookupMap.emplace(name,std::unique_ptr<Item>(this));
}
std::string Items::buildDescriptionName(ItemInstance const&) const
{
	return I18n::get(descriptionName);
}
unsigned long Items::getEnergy(ItemInstance const&i)const
{
	return ItemUtils::getEnergy(i);
}
void Items::onInteract(ItemInstance&)const
{
	
}
unsigned long Items::getMaxEnergy()const
{
	return 0;
}
bool Items::isEnergyStorageItem()const
{
	return false;
}
bool Items::canCharge()const
{
	return false;
}
void Items::registerItem(short id,std::string const&name,std::string const&tex,int a)
{
	Item::mItems[id]=new ICDefaultItem(name,id-0x100,tex,a);
}
void Items::registerItem(short id,std::string const&name,TextureUVCoordinateSet const&tex)
{
	Item::mItems[id]=new ICDefaultItem(name,id-0x100,tex);
}
void Items::registerItem(short id,std::string const&name,std::string const&tex,int a,CreativeItemCategory cate)
{
	Item::mItems[id]=new ICDefaultItem(name,id-0x100,tex,a);
	Item::mItems[id]->setCategory(cate);
}
void Items::registerItem(short id,std::string const&name,TextureUVCoordinateSet const&tex,CreativeItemCategory cate)
{
	Item::mItems[id]=new ICDefaultItem(name,id-0x100,tex);
	Item::mItems[id]->setCategory(cate);
}
std::string Items::getLoopingSound(ItemInstance&i)const
{
	return "";
}
void Items::registerItem(short id,std::string const&name,std::string const&tex,int a,int stack)
{
	Item::mItems[id]=new ICDefaultItem(name,id-0x100,tex,a);
	Item::mItems[id]->setMaxStackSize(stack);
}
void Items::registerItem(short id,std::string const&name,TextureUVCoordinateSet const&tex,int stack)
{
	Item::mItems[id]=new ICDefaultItem(name,id-0x100,tex);
	Item::mItems[id]->setMaxStackSize(stack);
}
void Items::addCreativeItemAuxData(short id,short max)
{
	for(short i=0;i<max;++i)
		Item::addCreativeItem(id,i);
}
}
