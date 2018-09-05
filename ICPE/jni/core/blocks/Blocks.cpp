#include "Blocks.h"

#include "mcpe/client/resources/I18n.h"

#include "block/RubberSaplingBlock.h"
#include "block/ResourcesBlock.h"
#include "block/ITNTBlock.h"
#include "block/RubberWoodBlock.h"
#include "block/ResinBlock.h"
#include "block/RubberLeavesBlock.h"
#include "block/CableBlock.h"
#include "block/ICFurnaceBlock.h"
#include "block/IronFenceBlock.h"
#include "block/GeneratorBlock1.h"
#include "block/MachineBlock1.h"
#include "block/BatBoxBlock.h"
#include "block/liquid/UUMatterFlowBlock.h"
#include "block/liquid/UUMatterStillBlock.h"
#include "block/LuminatorBlock.h"
#include "block/LuminatorActiveBlock.h"

#include <fstream>

IC::Blocks* IC::Blocks::mICBlocks[256];

namespace IC
{
void Blocks::initICBlocks()
{
	for(IC::Blocks* & block : mICBlocks)
		block=0;
	
	//Block::mBlocks[ID::mFurnace]=new ICFurnaceBlock();
	Block::mBlocks[ID::mCable]=new CableBlock();
	Block::mBlocks[ID::mRubberLeaves]=new RubberLeavesBlock();
	Block::mBlocks[ID::mResin]=new ResinBlock();
	Block::mBlocks[ID::mRubberWood]=new RubberWoodBlock();
	//Block::mBlocks[ID::mITNT]=new ITNTBlock();
	Block::mBlocks[ID::mRubberSapling]=new RubberSaplingBlock();
	Block::mBlocks[ID::mIronFence]=new IronFenceBlock();
	Block::mBlocks[ID::mResources]=new ResourcesBlock();
	//Block::mBlocks[ID::mGenerator1]=new GeneratorBlock1();
	//Block::mBlocks[ID::mUUMatterStill]=new UUMatterStillBlock();
	//Block::mBlocks[ID::mUUMatterFlow]=new UUMatterFlowBlock();
	//Block::mBlocks[ID::mLuminator]=new LuminatorBlock();
	//Block::mBlocks[ID::mLuminatorActive]=new LuminatorActiveBlock();
	//Block::mBlocks[ID::mMachine1]=new MachineBlock1();
	//Block::mBlocks[ID::mBatBox]=new BatBoxBlock();
}
std::string Blocks::buildDescriptionName(unsigned char) const
{
	return I18n::get(descriptionName);
}
bool Blocks::isElectricBlock(BlockSource&,BlockPos const&)const
{
	return false;
}
bool Blocks::isElectricConductor(BlockSource&,BlockPos const&)const
{
	return false;
}
bool Blocks::shouldExplodeOutOfVoltage(BlockSource&,BlockPos const&)const
{
	return false;
}
int Blocks::getElectricResistance(BlockSource&,BlockPos const&)const
{
	return 0;
}
int Blocks::getMaxVoltage(BlockSource&,BlockPos const&)const
{
	return INT_MAX;
}
bool Blocks::isElectricProvider(BlockSource&,BlockPos const&,FacingEnum)const
{
	return false;
}
bool Blocks::isElectricReceiver(BlockSource&,BlockPos const&,FacingEnum)const
{
	return false;
}
int Blocks::getNowVoltage(BlockSource&,BlockPos const&)const
{
	return 0;
}
Blocks::Blocks(std::string const&name,int id,Material const&m):Block(name,id,m)
{
	mICBlocks[id]=this;
	descriptionName=name;
	mBlockLookupMap.emplace(name,std::unique_ptr<Block>(this));
}
bool Blocks::isAnyAuxValueInRecipe()const
{
	return true;
}
bool Blocks::isICEntityBlock()const
{
	return false;
}
bool Blocks::isAllFace()const
{
	return false;
}
bool Blocks::isMachineBlock(BlockSource&,BlockPos const&)const
{
	return false;
}
}
