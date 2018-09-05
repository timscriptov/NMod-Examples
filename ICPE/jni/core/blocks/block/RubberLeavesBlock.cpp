#include "RubberLeavesBlock.h"

#include "mcpe/level/BlockSource.h"
#include "mcpe/item/ItemInstance.h"
#include "mcpe/block/blocks/FireBlock.h"
#include "mcpe/util/Random.h"
#include "mcpe/entity/player/Player.h"

#include "blocks/Blocks.h"
#include "util/Math.h"
#include "ICPE.h"

#include <stdlib.h>

RubberLeavesBlock::RubberLeavesBlock():IC::Blocks("leaves.rubber",IC::Blocks::ID::mRubberLeaves,Material::getMaterial(MaterialType::PLANT))
{
	init();
	setCategory(CreativeItemCategory::DECORATIONS);
	setSolid(false);
	setExplodeable(1);
	setDestroyTime(0.2);
	setTicking(true);
	setVisualShape({0.001,0.001,0.001,1,1,1});
	
	((FireBlock*)mFire)->setFlammable(BlockID(IC::Blocks::ID::mRubberLeaves),65,25);
}
int RubberLeavesBlock::getColor(BlockSource&s, BlockPos const&pos, unsigned char side) const
{
	return mLeaves->getColor(s,pos,side);
}
bool RubberLeavesBlock::isSeasonTinted(BlockSource&s, BlockPos const&pos) const
{
	return mLeaves->isSeasonTinted(s,pos);
}
int RubberLeavesBlock::getResource(Random&, int, int)const
{
	return IC::Blocks::ID::mRubberSapling;
}
int RubberLeavesBlock::getResourceCount(Random&r, int, int)const
{
	return r.nextBool(8)?1:0;
}
ItemInstance RubberLeavesBlock::getSilkTouchItemInstance(unsigned char)const
{
	return ItemInstance(IC::Blocks::ID::mRubberLeaves,1,0);
}
void RubberLeavesBlock::onGraphicsModeChanged(bool, bool, bool)
{
	
}
int RubberLeavesBlock::getRenderLayer(BlockSource&s, BlockPos const&pos) const
{
	return mLeaves->getRenderLayer(s,pos);
}
void RubberLeavesBlock::tick(BlockSource&s, BlockPos const&pos, Random&r)const
{
	if(r.nextBool(8)&&s.getData(pos)==0)
	{
		for(int sx=pos.x-4;sx<pos.x+4;++sx)
			for(int sy=pos.y-4;sy<pos.y+4;++sy)
				for(int sz=pos.z-4;sz<pos.z+4;++sz)
				{
					if(s.getBlockID(sx,sy,sz).id==ID::mRubberWood)
						if(isValidDistance(s,BlockPos(sx,sy,sz),pos))
							return;
				}
		die(s,pos,r);
	}
}
int RubberLeavesBlock::getPlacementDataValue(Entity&, BlockPos const&, signed char, Vec3 const&, int) const
{
	return 4;
}
void RubberLeavesBlock::die(BlockSource&s,BlockPos const&pos,Random&r)const
{
	s.removeBlock(pos);
	if(r.nextBool(8))
		popResource(s,pos,ItemInstance(ID::mRubberSapling,1,0));
}
bool RubberLeavesBlock::isValidDistance(BlockSource&s,BlockPos const&pos1,BlockPos const&pos2)const
{
	if((abs(pos1.x-pos2.x)+abs(pos1.y-pos2.y)+abs(pos1.z-pos2.z))>4)
		return false;
	
	int minX=Math::min(pos1.x,pos2.x);
	int maxX=Math::max(pos1.x,pos2.x);
	int minY=Math::min(pos1.y,pos2.y);
	int maxY=Math::max(pos1.y,pos2.y);
	int minZ=Math::min(pos1.z,pos2.z);
	int maxZ=Math::max(pos1.z,pos2.z);
	
	for(int posX=minX;posX<=maxX;++posX)
		for(int posY=minY;posY<=maxY;++posY)
			for(int posZ=minZ;posZ<=maxZ;++posZ)
				if(s.getBlock(posX,posY,posZ)!=this&&s.getBlock(posX,posY,posZ)!=mBlocks[ID::mRubberWood])
					return false;
	return true;
}
void RubberLeavesBlock::playerDestroy(Player*p, BlockPos const&pos, int aux)const
{
	if(p&&p->getSelectedItem()&&p->getSelectedItem()->getId()==359)
		popResource(p->getRegion(),pos,ItemInstance(ID::mRubberLeaves,1,0));
	else
		Block::playerDestroy(p,pos,aux);
}
