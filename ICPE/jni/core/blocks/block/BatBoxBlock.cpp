#if 0
#include "BatBoxBlock.h"

#include "mcpe/client/resources/I18n.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/entity/player/Player.h"
#include "mcpe/util/Random.h"
#include "ui/UIScreenChooser.h"
#include "ICPE.h"
#include "items/Items.h"
#include "blocks/blockentity/BatBoxBlockEntity.h"

BatBoxBlock::BatBoxBlock():BaseMachineBlock("te.batbox",IC::Blocks::ID::mBatBox,Material::getMaterial(MaterialType::METAL))
{
	init();
	setCategory(CreativeItemCategory::DECORATIONS);
	setDestroyTime(3);
	setExplodeable(10);
}
ICBlockEntity* BatBoxBlock::getBlockEntity(BlockSource&s,BlockPos const&pos)const
{
	int aux=s.getData(pos);
	
	switch(aux)
	{
	case 0:case 1:case 2:case 3:case 4:case 5:
		return new BatBoxBlockEntity(s,pos,this);
	}
}
bool BatBoxBlock::isElectricProvider(BlockSource&s,BlockPos const&pos,FacingEnum face)const
{
	short aux=s.getData(pos)%6;
	switch(face)
	{
	case FacingEnum::UP:
		return aux==1;
	case FacingEnum::DOWN:
		return aux==0;
	case FacingEnum::WEST:
		return aux==5;
	case FacingEnum::EAST:
		return aux==4;
	case FacingEnum::NORTH:
		return aux==3;
	case FacingEnum::SOUTH:
		return aux==2;
	case FacingEnum::ANY:
		return true;
	}
	return false;
}
bool BatBoxBlock::isElectricReceiver(BlockSource&s,BlockPos const&pos,FacingEnum face)const
{
	if(face==FacingEnum::ANY)
		return true;
	return !isElectricProvider(s,pos,face);
}
bool BatBoxBlock::isElectricBlock(BlockSource&,BlockPos const&)const
{
	return true;
}
std::string BatBoxBlock::buildDescriptionName(unsigned char aux) const
{
	switch(aux)
	{
	case 0:
		return I18n::get("te.batbox");
	}
	return "";
}
bool BatBoxBlock::hasComparatorSignal()const
{
	return true;
}
bool BatBoxBlock::use(Player&p, BlockPos const&pos) const
{
	if(BaseMachineBlock::use(p,pos))
		return true;
	switch(p.getRegion().getData(pos))
	{
	case 0:case 1:case 2:case 3:case 4:case 5:
		ICPE::mUIScreenChooser.pushBatBoxScreen(p,pos);
	break;
	}
	return true;
}
ItemInstance BatBoxBlock::getSilkTouchItemInstance(unsigned char aux) const
{
	return ItemInstance(ID::mBatBox,1,(aux-aux%6)/6);
}
int BatBoxBlock::getPlacementDataValue(Entity&ent, BlockPos const&pos, signed char side, Vec3 const&entPos, int aux) const
{
	return mPiston->getPlacementDataValue(ent,pos,side,entPos,0);
}
int BatBoxBlock::getComparatorSignal(BlockSource&, BlockPos const&, signed char, int)const
{
	return 1;
}
std::vector<ItemInstance> BatBoxBlock::getSpawnResources(int aux,Random&r)const
{
	/*switch(aux)
	{
	case 0:case 1:case 2:case 3:case 4:case 5:
		return std::vector<ItemInstance>
		{
			ItemInstance(IC::Items::ID::mReBattery,1,32766),
			ItemInstance(IC::Items::ID::mReBattery,1,32766),
			ItemInstance(IC::Items::ID::mReBattery,1,32766),
			ItemInstance(IC::Items::ID::mTinCable1,1,0)
		};
	break;
	}*/
	return std::vector<ItemInstance>();
}
bool BatBoxBlock::isAllFace()const
{
	return true;
}
#endif 
