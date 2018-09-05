#include "RubberSaplingBlock.h"

#include "mcpe/level/BlockSource.h"
#include "mcpe/level/Level.h"
#include "mcpe/entity/player/Player.h"
#include "mcpe/entity/EntityClassTree.h"
#include "mcpe/util/Random.h"

#include "gen/feature/RubTreeFeature.h"

#include "ICPE.h"

RubberSaplingBlock::RubberSaplingBlock():IC::Blocks("sapling.rubber",IC::Blocks::ID::mRubberSapling,Material::getMaterial(MaterialType::DEVICE))
{
	setCategory(CreativeItemCategory::DECORATIONS);
	setTicking(true);
	setSolid(false);
}
const AABB &RubberSaplingBlock::getCollisionShape(AABB&box, BlockSource&s, BlockPos const&pos, Entity*e)const
{
	return mSapling->getCollisionShape(box,s,pos,e);
}
void RubberSaplingBlock::tick(BlockSource&s, BlockPos const&pos, Random&r)const
{
	if(r.nextInt(25)==0)
		grow(s,pos,r);
}
void RubberSaplingBlock::onFertilized(BlockSource&s, BlockPos const&pos, Entity*e)const
{
	if(!(e&&EntityClassTree::isInstanceOf(*e,EntityType::PLAYER)))
		return;
	if(((Player*)e)->isCreative())
	{
		grow(s,pos,ICPE::mRandom);
		return;
	}
	else if(ICPE::mRandom.nextBool(7))
		grow(s,pos,ICPE::mRandom);
	makeParticles(s,pos,ICPE::mRandom);
	if(((Player*)e)->getSelectedItem())
	{
		--((Player*)e)->getSelectedItem()->count;
		if(((Player*)e)->getSelectedItem()->count==0)
			((Player*)e)->getSelectedItem()->setNull();
	}
}
bool RubberSaplingBlock::mayPlaceOn(Block const&b)const
{
	return mSapling->mayPlaceOn(b);
}
bool RubberSaplingBlock::canSurvive(BlockSource&s, BlockPos const&pos)const
{
	return mSapling->canSurvive(s,pos);
}
void RubberSaplingBlock::neighborChanged(BlockSource&s, BlockPos const&pos, BlockPos const&pos2)const
{
	if(!canSurvive(s,pos)&&s.getBlock(pos)==this)
	{
		s.removeBlock(pos);
		popResource(s,pos,ItemInstance(IC::Blocks::ID::mRubberSapling,1,0));
	}
}
bool RubberSaplingBlock::checkIsPathable(Entity&, BlockPos const&, BlockPos const&)const
{
	return true;
}
void RubberSaplingBlock::onGraphicsModeChanged(bool, bool, bool)
{
	
}
int RubberSaplingBlock::getRenderLayer(BlockSource&s, BlockPos const&pos) const
{
	return mSapling->getRenderLayer(s,pos);
}
int RubberSaplingBlock::getExtraRenderLayers() const
{
	return mSapling->getExtraRenderLayers();
}
bool RubberSaplingBlock::grow(BlockSource&s,BlockPos const&pos,Random&r)const
{
	IC::RubTreeFeature tree(FullBlock(ID::mRubberWood,0),FullBlock(ID::mRubberWood,2),FullBlock(ID::mRubberLeaves,0),15);
	tree.place(s,pos,r);
}
void RubberSaplingBlock::makeParticles(BlockSource&s,BlockPos const&pos,Random&r)const
{
	unsigned char particlesCount=10+r.nextInt(5);
	for(unsigned char mPos=0;mPos<particlesCount;++mPos)
		s.getLevel().addParticle((ParticleType)33,Vec3(pos.x+r.nextFloat(),pos.y+r.nextFloat(),pos.z+r.nextFloat()),Vec3(0,0,0),0);
}
bool RubberSaplingBlock::waterSpreadCausesSpawn() const
{
	return true;
}
