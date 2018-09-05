#pragma once

#include "mcpe/block/Block.h"
#include "util/FacingEnum.h"

namespace IC
{
class Blocks : public Block
{
public:
	class ID
	{
	public:
		static const unsigned short mResources=36;
		static const unsigned short mMachine1=210;
		static const unsigned short mKineticGenerator1=211;
		static const unsigned short mRubberWood=210;
		static const unsigned short mRubberLeaves=211;
		static const unsigned short mRubberSapling=212;
		static const unsigned short mITNT=215;
		static const unsigned short mResin=204;
		static const unsigned short mCable=205;
		static const unsigned short mFurnace=218;
		static const unsigned short mIronFence=209;
		static const unsigned short mEmpty=221;
		static const unsigned short mGenerator1=222;
		static const unsigned short mBatBox=223;
		static const unsigned short mTransformer=224;
		static const unsigned short mUUMatterFlow=230;
		static const unsigned short mUUMatterStill=231;
		static const unsigned short mLuminator=232;
		static const unsigned short mLuminatorActive=233;
	};
public:
	static Blocks* mICBlocks[256];
public:
	static void initICBlocks();
private:
	std::string descriptionName;
public:
	Blocks(std::string const&,int,Material const&);
public:
	virtual bool isMachineBlock(BlockSource&,BlockPos const&)const;
	virtual bool isElectricBlock(BlockSource&,BlockPos const&)const;
	virtual bool isElectricProvider(BlockSource&,BlockPos const&,FacingEnum)const;
	virtual bool isElectricReceiver(BlockSource&,BlockPos const&,FacingEnum)const;
	virtual bool isElectricConductor(BlockSource&,BlockPos const&)const;
	virtual bool shouldExplodeOutOfVoltage(BlockSource&,BlockPos const&)const;
	virtual int getElectricResistance(BlockSource&,BlockPos const&)const;
	virtual int getMaxVoltage(BlockSource&,BlockPos const&)const;
	virtual int getNowVoltage(BlockSource&,BlockPos const&)const;
	virtual bool isAnyAuxValueInRecipe()const;
	virtual std::string buildDescriptionName(unsigned char) const;
	virtual bool isICEntityBlock()const;
	virtual bool isAllFace()const;
};
}
