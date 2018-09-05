#include "ICFurnaceBlock.h"
#if 0
#include "ICPE.h"
#include "ui/UIScreenChooser.h"
#include "items/Items.h"
#include "mcpe/item/ItemInstance.h"
#include "mcpe/entity/player/Player.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/client/resources/I18n.h"
#include "blocks/blockentity/IronFurnaceBlockEntity.h"
#include "blocks/blockentity/ElectricFurnaceBlockEntity.h"

ICFurnaceBlock::ICFurnaceBlock():BaseMachineBlock("ic.furnace",IC::Blocks::ID::mFurnace,Material::getMaterial(MaterialType::STONE))
{
	init();
	setCategory(CreativeItemCategory::DECORATIONS);
	setSolid(true);
	setDestroyTime(3);
	setExplodeable(15);
}
std::string ICFurnaceBlock::buildDescriptionName(unsigned char aux) const
{
	if(aux==0)
		return I18n::get("te.iron_furnace");
	if(aux==1)
		return I18n::get("te.electric_furnace");
	return "";
}
int ICFurnaceBlock::getPlacementDataValue(Entity&e, BlockPos const&pos, signed char side, Vec3 const&pixel, int aux)const
{
	if(aux==0)
		return mFurnace->getPlacementDataValue(e,pos,side,pixel,0)-2;
	else if(aux==1)
		return mFurnace->getPlacementDataValue(e,pos,side,pixel,0)+2;
}
bool ICFurnaceBlock::use(Player&p, BlockPos const&pos)const
{
	if(BaseMachineBlock::use(p,pos))
		return true;
	switch(p.getRegion().getData(pos))
	{
	case 0:case 1:case 2:case 3:
		ICPE::mUIScreenChooser.pushIronFurnaceScreen(p,pos);
		break;
	case 4:case 5:case 6:case 7:
		ICPE::mUIScreenChooser.pushElectricFurnaceScreen(p,pos);
		break;
	}
	return true;
}
ICBlockEntity* ICFurnaceBlock::getBlockEntity(BlockSource&s,BlockPos const&pos)const
{
	switch(s.getData(pos))
	{
	case 0:case 1:case 2:case 3:
		return new IronFurnaceBlockEntity(s,pos,this);
	case 4:case 5:case 6:case 7:
		return new ElectricFurnaceBlockEntity(s,pos,this);
	}
	return 0;
}
bool ICFurnaceBlock::isElectricBlock(BlockSource&s,BlockPos const&pos)const
{
	return s.getData(pos)>=4;
}
bool ICFurnaceBlock::isElectricReceiver(BlockSource&s,BlockPos const&pos,FacingEnum)const
{
	return s.getData(pos)>=4;
}
std::vector<ItemInstance> ICFurnaceBlock::getSpawnResources(int aux,Random&r)const
{
	/*switch(aux)
	{
	case 0:case 1:case 2:case 3:
		return std::vector<ItemInstance>
		{
			ItemInstance(IC::Blocks::ID::mFurnace,1,0)
		};
	case 4:case 5:case 6:case 7:
		return std::vector<ItemInstance>
		{
			ItemInstance(IC::Blocks::ID::mFurnace,1,0),
			ItemInstance(IC::Items::ID::mCircuit,1,0)
		};
	}*/
	return std::vector<ItemInstance>();
}
#endif
