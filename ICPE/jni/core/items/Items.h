#pragma once

#include "mcpe/item/Item.h"

class TextureUVCoordinateSet;

namespace IC
{
class Items : public Item
{
public:
	class ID
	{
	public:
		static const short mResources=453;
		static const short mCable=454;
		static const short mDischargedChainsaw=500;
		static const short mPainter=455;
		static const short mTreeTap=503;
		static const short mReBattery=506;
		static const short mCutter=507;
		static const short mWrench=509;
		static const short mForgeHammer=512;
		static const short mElectricTreeTap=513;
		static const short mElectricWrench=514;
		static const short mElectricHoe=518;
		static const short mChainsaw=519;
		static const short mSingleUseBattery=520;
		static const short mMeter=706;
		static const short mChargingReBattery=707;
		static const short mBoots_bronze=708;
		static const short mHelmet_bronze=709;
		static const short mLeggings_bronze=710;
		static const short mChestplate_bronze=711;
		static const short mWindMeter=712;
		static const short mChainsaw2=713;

		static const short mDischargedChainsaw2=714;
	};
public:
	static void initICAllItems();
	static void teardownICItems();
	static void addICCreativeItems();
private:
	static void initICItems();
	static void initICBlockItems();
public:
	static Items* mICItems[4096];
	static bool hasTeardown;
public:
	Items(std::string const&,short);
private:
	std::string descriptionName;
public:
	virtual unsigned long getEnergy(ItemInstance const&)const;
	virtual unsigned long getMaxEnergy()const;
	virtual unsigned int getIVoltage()const;
	virtual unsigned int getOVoltage()const;
	virtual bool isEnergyStorageItem()const;
	virtual bool canCharge()const;
	virtual void onInteract(ItemInstance&)const;
	virtual std::string getLoopingSound(ItemInstance&)const;
	virtual std::string buildDescriptionName(ItemInstance const&) const;
public:
	static void addCreativeItemAuxData(short,short);
	static void registerItem(short,std::string const&,std::string const&,int);
	static void registerItem(short,std::string const&,TextureUVCoordinateSet const&);
	static void registerItem(short,std::string const&,std::string const&,int,CreativeItemCategory);
	static void registerItem(short,std::string const&,TextureUVCoordinateSet const&,CreativeItemCategory);
	static void registerItem(short,std::string const&,std::string const&,int,int);
	static void registerItem(short,std::string const&,TextureUVCoordinateSet const&,int);
};
}
