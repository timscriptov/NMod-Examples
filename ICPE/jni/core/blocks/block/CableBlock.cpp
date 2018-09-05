#include "CableBlock.h"

#include "items/Items.h"
#include "blocks/Blocks.h"

#include "mcpe/item/Item.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/entity/Entity.h"
#include "mcpe/entity/Mob.h"
#include "mcpe/entity/EntityClassTree.h"
#include "mcpe/util/EntityDamageSource.h"

#include "util/CableUtil.h"

#include "blocks/blockentity/CableBlockEntity.h"

#include "ICPE.h"

CableBlock::CableBlock():CEntityBlock("cable_block",IC::Blocks::ID::mCable,Material::getMaterial(MaterialType::DEVICE))
{
	init();
	setSolid(false);
	setExplodeable(6);
	setDestroyTime(1.5);
}
void CableBlock::addCollisionShapes(BlockSource&s, BlockPos const&pos, AABB const*pAABB, std::vector<AABB, std::allocator<AABB> >&list,Entity*) const
{
	float defaultDistance=CableUtil::getSize(s.getData(pos));
	
	if(CableUtil::canConnectTo(s,pos,{pos.x,pos.y+1,pos.z}))
		list.push_back({pos.x+defaultDistance,pos.y+1-defaultDistance,pos.z+defaultDistance,pos.x+1-defaultDistance,pos.y+1,pos.z+1-defaultDistance});
	if(CableUtil::canConnectTo(s,pos,{pos.x,pos.y-1,pos.z}))
		list.push_back({pos.x+defaultDistance,pos.y,pos.z+defaultDistance,pos.z+1-defaultDistance,pos.y+defaultDistance,pos.z+1-defaultDistance});
	if(CableUtil::canConnectTo(s,pos,{pos.x,pos.y,pos.z+1}))
		list.push_back({pos.x+defaultDistance,pos.y+defaultDistance,pos.z+1-defaultDistance,pos.x+1-defaultDistance,pos.y+1-defaultDistance,1});
	if(CableUtil::canConnectTo(s,pos,{pos.x,pos.y,pos.z-1}))
		list.push_back({pos.x+defaultDistance,pos.y+defaultDistance,pos.z,pos.x+1-defaultDistance,pos.y+1-defaultDistance,pos.z+defaultDistance});
	if(CableUtil::canConnectTo(s,pos,{pos.x+1,pos.y,pos.z}))
		list.push_back({pos.x+1-defaultDistance,pos.y+defaultDistance,pos.z+defaultDistance,pos.x+1,pos.y+1-defaultDistance,pos.z+1-defaultDistance});
	if(CableUtil::canConnectTo(s,pos,{pos.x-1,pos.y,pos.z}))
		list.push_back({pos.x,pos.y+defaultDistance,pos.z+defaultDistance,pos.x+defaultDistance,pos.y+1-defaultDistance,pos.z+1-defaultDistance});
	list.push_back({pos.x+defaultDistance,pos.y+defaultDistance,pos.z+defaultDistance,pos.x+1-defaultDistance,pos.y+1-defaultDistance,pos.z+1-defaultDistance});
	Block::addAABBs(s,pos,pAABB,list);
}
bool CableBlock::detachesOnPistonMove(BlockSource&, BlockPos const&)const
{
	return true;
}
int CableBlock::getResource(Random&, int aux,int)const
{
	return IC::Items::ID::mCable;
}
int CableBlock::getResourceCount(Random&, int, int)const
{
	return 1;
}
bool CableBlock::canBeSilkTouched() const
{
	return false;
}
int CableBlock::getSpawnResourcesAuxValue(unsigned char i)const
{
	return i;
}
std::string CableBlock::buildDescriptionName(unsigned char aux) const
{
	return "cable";
}
void CableBlock::neighborChanged(BlockSource&, BlockPos const&, BlockPos const&)const
{
	
}
bool CableBlock::entityInside(BlockSource&s, BlockPos const&pos, Entity&e)const
{
	if(!CableUtil::isUninsulated(s.getData(pos)))
		return false;
	CableBlockEntity* cbe=(CableBlockEntity*)s.getBlockEntity(pos);
	if(cbe&&cbe->getEnergyConducted().getVoltage()>0)
	{
		e.doFireHurt(CableUtil::getHurt(cbe->getEnergyConducted().getVoltage()));
		e.setOnFire(CableUtil::getFire(cbe->getEnergyConducted().getEnergy()));
	}
	return true;
}
bool CableBlock::hasComparatorSignal()const
{
	return true;
}
int CableBlock::getComparatorSignal(BlockSource&, BlockPos const&, signed char, int)const
{
	return 1;
}
int CableBlock::getRenderLayer(BlockSource&s, BlockPos const&pos) const
{
	return mGlass->getRenderLayer(s,pos);
}
int CableBlock::getPlacementDataValue(Entity&, BlockPos const&, signed char, Vec3 const&, int aux) const
{
	return aux;
}
AABB const& CableBlock::getVisualShape(BlockSource&s, BlockPos const&pos, AABB&, bool) const
{
	float defaultDistance=CableUtil::getSize(s.getData(pos));
	return {defaultDistance,defaultDistance,defaultDistance,1-defaultDistance,1-defaultDistance,1-defaultDistance};
}
AABB const&CableBlock::getVisualShape(unsigned char aux, AABB&, bool) const
{
	float defaultDistance=CableUtil::getSize(aux);
	return {defaultDistance,defaultDistance,defaultDistance,1-defaultDistance,1-defaultDistance,1-defaultDistance};
}
bool CableBlock::isElectricConductor(BlockSource&,BlockPos const&)const
{
	return true;
}
std::unique_ptr<CBlockEntity> CableBlock::createBlockEntity(BlockPos const&pos)const
{
	return std::unique_ptr<CBlockEntity>(new CableBlockEntity(pos));
}
