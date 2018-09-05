#include "RubTreeFeature.h"

#include "mcpe/level/BlockSource.h"
#include "mcpe/util/BlockPos.h"
#include "mcpe/util/FullBlock.h"
#include "mcpe/util/Random.h"
#include "mcpe/block/Block.h"

#include "blocks/Blocks.h"

#include <stdlib.h>

namespace IC
{
RubTreeFeature::RubTreeFeature(FullBlock const&l,FullBlock const&ll,FullBlock const&le,int max):Feature(0)
{
	log=l;
	log2=ll;
	leaf=le;
	maxTreeHeight=max;
}
bool RubTreeFeature::place(BlockSource&s,BlockPos const&pos,Random&r)const
{
	return grow(s,pos,r);
}
bool RubTreeFeature::grow(BlockSource&world,BlockPos const&pos_,Random&random)const
{
	BlockPos pos=pos_;
	int treeholechance = 25;
	int height = getGrowHeight(world, pos);
	if (height < 2)
		return false;
	height -= random.nextInt(height / 2 + 1);
	
	int x=pos.x,y=pos.y,z=pos.z;
	world.setBlockAndData(x, y - 1, z, FullBlock(3,0),3);
	char width = 3;
	char var18 = 0;
	for (int cz = y - width + height; cz <= y + height; ++cz)
	{
		int number = cz - (y + height);
		int treeWidth = var18 + 1 - number / 2;
		for (int tx = x - treeWidth; tx <= x + treeWidth; ++tx)
		{
			int var15 = tx - x;
			for (int tz = z - treeWidth; tz <= z + treeWidth; ++tz)
			{
				int var17 = tz - z;
				if(canBeReplacedByLeaves(world,BlockPos(tx,cz,tz)))
					world.setBlockAndData(tx, cz, tz, leaf ,3);
			}
		}
	}
	
	if(world.getBlock(x+1,y+height,z+1)==Block::mBlocks[IC::Blocks::ID::mRubberLeaves])
		world.removeBlock(x+1,y+height,z+1);
	if(world.getBlock(x-1,y+height,z+1)==Block::mBlocks[IC::Blocks::ID::mRubberLeaves])
		world.removeBlock(x-1,y+height,z+1);
	if(world.getBlock(x+1,y+height,z-1)==Block::mBlocks[IC::Blocks::ID::mRubberLeaves])
		world.removeBlock(x+1,y+height,z-1);
	if(world.getBlock(x-1,y+height,z-1)==Block::mBlocks[IC::Blocks::ID::mRubberLeaves])
		world.removeBlock(x-1,y+height,z-1);
	
	if(random.nextBool()&&world.getBlock(x+2,y+height-2,z+2)==Block::mBlocks[IC::Blocks::ID::mRubberLeaves])world.removeBlock(x+2,y+height-2,z+2);
	if(random.nextBool()&&world.getBlock(x-2,y+height-2,z+2)==Block::mBlocks[IC::Blocks::ID::mRubberLeaves])world.removeBlock(x-2,y+height-2,z+2);
	if(random.nextBool()&&world.getBlock(x+2,y+height-2,z-2)==Block::mBlocks[IC::Blocks::ID::mRubberLeaves])world.removeBlock(x+2,y+height-2,z-2);
	if(random.nextBool()&&world.getBlock(x-2,y+height-2,z-2)==Block::mBlocks[IC::Blocks::ID::mRubberLeaves])world.removeBlock(x-2,y+height-2,z-2);
	if(random.nextBool()&&world.getBlock(x+2,y+height-3,z+2)==Block::mBlocks[IC::Blocks::ID::mRubberLeaves])world.removeBlock(x+2,y+height-2,z+2);
	if(random.nextBool()&&world.getBlock(x-2,y+height-3,z+2)==Block::mBlocks[IC::Blocks::ID::mRubberLeaves])world.removeBlock(x-2,y+height-2,z+2);
	if(random.nextBool()&&world.getBlock(x+2,y+height-3,z-2)==Block::mBlocks[IC::Blocks::ID::mRubberLeaves])world.removeBlock(x+2,y+height-2,z-2);
	if(random.nextBool()&&world.getBlock(x-2,y+height-3,z-2)==Block::mBlocks[IC::Blocks::ID::mRubberLeaves])world.removeBlock(x-2,y+height-2,z-2);
	if(random.nextBool()&&world.getBlock(x+1,y+height-1,z+1)==Block::mBlocks[IC::Blocks::ID::mRubberLeaves])world.removeBlock(x+1,y+height-1,z+1);
	if(random.nextBool()&&world.getBlock(x-1,y+height-1,z+1)==Block::mBlocks[IC::Blocks::ID::mRubberLeaves])world.removeBlock(x-1,y+height-1,z+1);
	if(random.nextBool()&&world.getBlock(x+1,y+height-1,z-1)==Block::mBlocks[IC::Blocks::ID::mRubberLeaves])world.removeBlock(x+1,y+height-1,z-1);
	if(random.nextBool()&&world.getBlock(x-1,y+height-1,z-1)==Block::mBlocks[IC::Blocks::ID::mRubberLeaves])world.removeBlock(x-1,y+height-1,z-1);
	
	BlockPos tmpPos;
	
	for (int cHeight = 0; cHeight < height; ++cHeight)
	{
		BlockPos cPos = BlockPos(pos.x,pos.y+cHeight,pos.z);
		
		if (random.nextInt(100) <= treeholechance) 
		{
			treeholechance -= 10;
			world.setBlockAndData(cPos,{log2.id,7+random.nextInt(3)},3,0);
		}
		else
			world.setBlockAndData(cPos,log,3,0);
	}
	
	for (int i = 0; i <= height / 4 + random.nextInt(2); ++i)
	{
		tmpPos=BlockPos(pos.x, pos.y + height + i, pos.z);
		if (canBeReplacedByLeaves(world,tmpPos))
			world.setBlockAndData(tmpPos,leaf,3,0);
	}
	return true;
}
int RubTreeFeature::getGrowHeight(BlockSource&world,BlockPos const&pos_)const
{
	BlockPos pos=pos_;
	
	int height = 1;
	++pos.y;
	
	while ((canBeReplacedByWood(world,pos) && (height < 8) && (height < maxTreeHeight)))
	{
		++pos.y;
		++height;
	}
	return height;
}
bool RubTreeFeature::canBeReplacedByLeaves(BlockSource&s,BlockPos const&pos)const
{
	return s.getBlock(pos)==Block::mAir||s.getBlock(pos)==Block::mLeaves||s.getBlock(pos)==Block::mLeaves2||s.getBlock(pos)==Block::mVine||s.getBlock(pos)==Block::mTallgrass||s.getBlock(pos)==Block::mDeadBush||s.getBlock(pos)==Block::mYellowFlower||s.getBlock(pos)==Block::mRedFlower||s.getBlock(pos)==Block::mRedMushroom||s.getBlock(pos)==Block::mBrownMushroom||s.getBlock(pos)==Block::mReeds||s.getBlock(pos)==Block::mCocoa||s.getBlock(pos)==Block::mSapling||s.getBlockID(pos).id==leaf.id.id;
}
bool RubTreeFeature::canBeReplacedByWood(BlockSource&s,BlockPos const&pos)const
{
	return s.getBlock(pos)==Block::mAir||s.getBlock(pos)==Block::mLeaves||s.getBlock(pos)==Block::mLeaves2||s.getBlock(pos)==Block::mVine||s.getBlock(pos)==Block::mTallgrass||s.getBlock(pos)==Block::mDeadBush||s.getBlock(pos)==Block::mYellowFlower||s.getBlock(pos)==Block::mRedFlower||s.getBlock(pos)==Block::mRedMushroom||s.getBlock(pos)==Block::mBrownMushroom||s.getBlock(pos)==Block::mReeds||s.getBlock(pos)==Block::mCocoa||s.getBlock(pos)==Block::mSapling||s.getBlockID(pos).id==leaf.id.id;
}
}
