#include "FallenRubTreeFeature.h"

#include "mcpe/level/BlockSource.h"
#include "mcpe/util/BlockPos.h"
#include "mcpe/util/FullBlock.h"
#include "mcpe/util/Random.h"
#include "mcpe/block/Block.h"

#include "blocks/Blocks.h"

#include <stdlib.h>

namespace IC
{
FallenRubTreeFeature::FallenRubTreeFeature(FullBlock const&l):Feature(0)
{
	log=l;
}
bool FallenRubTreeFeature::place(BlockSource&s,BlockPos const&pos,Random&r)const
{
	return placeFallen(s,pos,r);
}
bool FallenRubTreeFeature::placeFallen(BlockSource&s,BlockPos const&pos,Random&r)const
{
	int x=pos.x,y=pos.y,z=pos.z;
	
	s.setBlockAndData(x, y - 1, z, FullBlock(3,0),3);
	s.setBlockAndData(x, y, z, log,3);
	
	int size=3+r.nextInt(2);
	
	switch(r.nextInt(4))
	{
	case 0:
		for(int posX=x+2;posX<x+size+2;++posX)
			if(canBeReplacedByWood(s,BlockPos(posX,y,z)))
			{
				s.setBlockAndData(posX, y , z, log.id,2,3);
				if(r.nextBool(4))
					s.setBlockAndData(posX, y+1 , z, r.nextBool()?39:40,0,3);
			}
			else 
				return false;
	break;
	case 1:
		for(int posX=x-2;posX>x-size-2;--posX)
			if(canBeReplacedByWood(s,BlockPos(posX,y,z)))
			{
				s.setBlockAndData(posX, y , z, log.id,2,3);
				if(r.nextBool(4))
					s.setBlockAndData(posX, y+1 , z, r.nextBool()?39:40,0,3);
			}
			else
				return false;
	break;
	case 2:
		for(int posZ=z+2;posZ<z+size+2;++posZ)
			if(canBeReplacedByWood(s,BlockPos(x,y,posZ)))
			{
				s.setBlockAndData(x, y , posZ, log.id,1,3);
				if(r.nextBool(4))
					s.setBlockAndData(x, y+1 , posZ, r.nextBool()?39:40,0,3);
			}
			else
				return false;
	break;
	case 3:
		for(int posZ=z-2;posZ>z-size-2;--posZ)
			if(canBeReplacedByWood(s,BlockPos(x,y,posZ)))
			{
				s.setBlockAndData(x, y , posZ, log.id,1,3);
				if(r.nextBool(4))
					s.setBlockAndData(x, y+1 , posZ, r.nextBool()?39:40,0,3);
			}
			else
				return false;
	break;
	}
	if(r.nextBool(3))
	{
		if(canBeReplacedByLeaves(s,BlockPos(x+1,y,z)))
			s.setBlockAndData(x+1,y,z,106,2,3);
		if(canBeReplacedByLeaves(s,BlockPos(x-1,y,z)))
			s.setBlockAndData(x-1,y,z,106,8,3);
		if(canBeReplacedByLeaves(s,BlockPos(x,y,z+1)))
			s.setBlockAndData(x,y,z+1,106,4,3);
		if(canBeReplacedByLeaves(s,BlockPos(x,y,z-1)))
			s.setBlockAndData(x,y,z-1,106,1,3);
	}
	return true;
}
bool FallenRubTreeFeature::canBeReplacedByLeaves(BlockSource&s,BlockPos const&pos)const
{
	return s.getBlock(pos)==Block::mAir||s.getBlock(pos)==Block::mLeaves||s.getBlock(pos)==Block::mLeaves2||s.getBlock(pos)==Block::mVine||s.getBlock(pos)==Block::mTallgrass||s.getBlock(pos)==Block::mDeadBush||s.getBlock(pos)==Block::mYellowFlower||s.getBlock(pos)==Block::mRedFlower||s.getBlock(pos)==Block::mRedMushroom||s.getBlock(pos)==Block::mBrownMushroom||s.getBlock(pos)==Block::mReeds||s.getBlock(pos)==Block::mCocoa||s.getBlock(pos)==Block::mSapling;
}
bool FallenRubTreeFeature::canBeReplacedByWood(BlockSource&s,BlockPos const&pos)const
{
	return s.getBlock(pos)==Block::mAir||s.getBlock(pos)==Block::mLeaves||s.getBlock(pos)==Block::mLeaves2||s.getBlock(pos)==Block::mVine||s.getBlock(pos)==Block::mTallgrass||s.getBlock(pos)==Block::mDeadBush||s.getBlock(pos)==Block::mYellowFlower||s.getBlock(pos)==Block::mRedFlower||s.getBlock(pos)==Block::mRedMushroom||s.getBlock(pos)==Block::mBrownMushroom||s.getBlock(pos)==Block::mReeds||s.getBlock(pos)==Block::mCocoa||s.getBlock(pos)==Block::mSapling;
}
}
