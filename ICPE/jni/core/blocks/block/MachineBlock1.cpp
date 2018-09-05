#if 0
#include "MachineBlock1.h"

#include "mcpe/client/resources/I18n.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/entity/player/Player.h"
#include "mcpe/util/Random.h"
#include "ui/UIScreenChooser.h"
#include "ICPE.h"
#include "items/Items.h"

#include "blocks/blockentity/MaceratorBlockEntity.h"
#include "blocks/blockentity/ExtractorBlockEntity.h"
#include "blocks/blockentity/CompressorBlockEntity.h"

MachineBlock1::MachineBlock1():BaseMachineBlock("ic.machine",IC::Blocks::ID::mMachine1,Material::getMaterial(MaterialType::METAL))
{
	init();
	setCategory(CreativeItemCategory::DECORATIONS);
	setDestroyTime(3);
	setExplodeable(10);
}
ICBlockEntity* MachineBlock1::getBlockEntity(BlockSource&s,BlockPos const&pos)const
{
	int aux=s.getData(pos);
	
	switch(aux)
	{
	case 0:case 1:case 2:case 3:
		return new MaceratorBlockEntity(s,pos,this);
	case 4:case 5:case 6:case 7:
		return new ExtractorBlockEntity(s,pos,this);
	case 8:case 9:case 10:case 11:
		return new CompressorBlockEntity(s,pos,this);
	}
}
bool MachineBlock1::isElectricReceiver(BlockSource&s,BlockPos const&pos,FacingEnum face)const
{
	return true;
}
bool MachineBlock1::isElectricBlock(BlockSource&,BlockPos const&)const
{
	return true;
}
std::string MachineBlock1::buildDescriptionName(unsigned char aux) const
{
	switch(aux)
	{
	case 0:
		return I18n::get("te.macerator");
	case 1:
		return I18n::get("te.extractor");
	case 2:
		return I18n::get("te.compressor");
	}
	return "";
}
bool MachineBlock1::hasComparatorSignal()const
{
	return true;
}
bool MachineBlock1::use(Player&p, BlockPos const&pos) const
{
	if(BaseMachineBlock::use(p,pos))
		return true;
	switch(p.getRegion().getData(pos))
	{
	case 0:case 1:case 2:case 3:
		ICPE::mUIScreenChooser.pushMaceratorScreen(p,pos);
	break;
	case 4:case 5:case 6:case 7:
		ICPE::mUIScreenChooser.pushExtractorScreen(p,pos);
	break;
	case 8:case 9:case 10:case 11:
		ICPE::mUIScreenChooser.pushCompressorScreen(p,pos);
	break;
	}
	return true;
}
ItemInstance MachineBlock1::getSilkTouchItemInstance(unsigned char aux) const
{
	return ItemInstance(ID::mMachine1,1,(aux-aux%4)/4);
}
int MachineBlock1::getPlacementDataValue(Entity&ent, BlockPos const&pos, signed char side, Vec3 const&entPos, int aux) const
{
	return (mFurnace->getPlacementDataValue(ent,pos,side,entPos,0)-2)+aux*4;
}
int MachineBlock1::getComparatorSignal(BlockSource&, BlockPos const&, signed char, int)const
{
	return 1;
}
std::vector<ItemInstance> MachineBlock1::getSpawnResources(int aux,Random&r)const
{
	/*switch(aux)
	{
	case 0:case 1:case 2:case 3:
		return std::vector<ItemInstance>
		{
			ItemInstance(IC::Blocks::ID::mResources,1,4),
			ItemInstance(4,2,0),
			ItemInstance(IC::Items::ID::mCircuit,1,0),
			ItemInstance(318,1+r.nextInt(3),0)
		};
	case 4:case 5:case 6:case 7:
		return std::vector<ItemInstance>
		{
			ItemInstance(IC::Blocks::ID::mResources,1,4),
			ItemInstance(IC::Items::ID::mCircuit,1,0)
		};
	case 8:case 9:case 10:case 11:
		return std::vector<ItemInstance>
		{
			ItemInstance(IC::Blocks::ID::mResources,1,4),
			ItemInstance(IC::Items::ID::mCircuit,1,0),
			ItemInstance(1,r.nextInt(5),0)
		};
	}*/
	return std::vector<ItemInstance>();
}
#endif
