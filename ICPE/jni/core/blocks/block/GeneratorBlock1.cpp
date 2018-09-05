#if 0
#include "GeneratorBlock1.h"

#include "mcpe/client/resources/I18n.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/entity/player/Player.h"
#include "ui/UIScreenChooser.h"
#include "ICPE.h"
#include "items/Items.h"
#include "mcpe/util/Random.h"
#include "blocks/blockentity/SolarGeneratorBlockEntity.h"
#include "blocks/blockentity/FireGeneratorBlockEntity.h"

GeneratorBlock1::GeneratorBlock1():BaseMachineBlock("ic.generator",IC::Blocks::ID::mGenerator1,Material::getMaterial(MaterialType::METAL))
{
	init();
	setCategory(CreativeItemCategory::DECORATIONS);
	setDestroyTime(3);
	setExplodeable(10);
}
ICBlockEntity* GeneratorBlock1::getBlockEntity(BlockSource&s,BlockPos const&pos)const
{
	int aux=s.getData(pos);
	
	switch(aux)
	{
	case 0:case 1:case 2:case 3:
		return new SolarGeneratorBlockEntity(s,pos,this);
	case 4:case 5:case 6:case 7:
		return new FireGeneratorBlockEntity(s,pos,this);
	}
}
bool GeneratorBlock1::isElectricProvider(BlockSource&s,BlockPos const&pos,FacingEnum face)const
{
	return true;
}
bool GeneratorBlock1::isElectricBlock(BlockSource&,BlockPos const&)const
{
	return true;
}
std::string GeneratorBlock1::buildDescriptionName(unsigned char aux) const
{
	switch(aux)
	{
	case 0:
		return I18n::get("te.solar_generator");
	case 1:
		return I18n::get("te.generator");
	}
	return "";
}
bool GeneratorBlock1::hasComparatorSignal()const
{
	return true;
}
bool GeneratorBlock1::use(Player&p, BlockPos const&pos) const
{
	if(BaseMachineBlock::use(p,pos))
		return true;
	switch(p.getRegion().getData(pos))
	{
	case 0:case 1:case 2:case 3:
		ICPE::mUIScreenChooser.pushSolarGeneratorScreen(p,pos);
	break;
	case 4:case 5:case 6:case 7:
		ICPE::mUIScreenChooser.pushFireGeneratorScreen(p,pos);
	break;
	}
	return true;
}
ItemInstance GeneratorBlock1::getSilkTouchItemInstance(unsigned char aux) const
{
	return ItemInstance(ID::mGenerator1,1,(aux-aux%4)/4);
}
int GeneratorBlock1::getPlacementDataValue(Entity&ent, BlockPos const&pos, signed char side, Vec3 const&entPos, int aux) const
{
	return (mFurnace->getPlacementDataValue(ent,pos,side,entPos,0)-2)+aux*4;
}
int GeneratorBlock1::getComparatorSignal(BlockSource&, BlockPos const&, signed char, int)const
{
	return 1;
}
std::vector<ItemInstance> GeneratorBlock1::getSpawnResources(int aux,Random&r)const
{
	/*switch(aux)
	{
	case 0:case 1:case 2:case 3:
		return std::vector<ItemInstance>
		{
			ItemInstance(IC::Blocks::ID::mResources,1,4),
			ItemInstance(IC::Items::ID::mCoalDust,1+r.nextInt(3),0),
			ItemInstance(IC::Items::ID::mCircuit,1+r.nextInt(2),0)
		};
	case 4:case 5:case 6:case 7:
		return std::vector<ItemInstance>
		{
			ItemInstance(IC::Blocks::ID::mFurnace,1,0),
			ItemInstance(IC::Items::ID::mCircuit,1,0),
			ItemInstance(IC::Items::ID::mReBattery,1,32766)
		};
	}*/
	return std::vector<ItemInstance>();
}
#endif
