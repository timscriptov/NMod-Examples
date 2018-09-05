#include "ICMachineBlockEntity.h"

#include "mcpe/level/Level.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/util/Vec3.h"
#include "mca/data/Database.h"
#include "items/Items.h"

ICMachineBlockEntity::ICMachineBlockEntity(BlockPos const&pos,int i)
:ContainerBlockEntity(pos,i)
{
	redstoneInverter=false;
	energyStorageUpgrade=false;
	overlockerUpgrade=false;
	transformerUpgrade=false;
	directionType=DirectionType::NONE;
	moveType=MoveType::NONE;
}
void ICMachineBlockEntity::load(mca::CompoundTag const&tag)
{
	ContainerBlockEntity::load(tag);
	redstoneInverter=tag.getBool("redstoneInverter");
	energyStorageUpgrade=tag.getBool("energyStorageUpgrade");
	overlockerUpgrade=tag.getBool("overlockerUpgrade");
	transformerUpgrade=tag.getBool("transformerUpgrade");
	directionType=(DirectionType)tag.getInt("directionType");
	moveType=(MoveType)tag.getInt("moveType");
}
void ICMachineBlockEntity::explode()
{
	//getRegion().getLevel().destroyBlock(getRegion(),pos,true);
	//getRegion().getLevel().explode(getRegion(),0,Vec3(pos.x+0.5,pos.y+0.5,pos.z+0.5),1,true,false,1);
}
bool ICMachineBlockEntity::isMachine()const
{
	return true;
}
void ICMachineBlockEntity::save(mca::CompoundTag &tag)const
{
	ContainerBlockEntity::save(tag);
	tag.putBool("redstoneInverter",redstoneInverter);
	tag.putBool("energyStorageUpgrade",energyStorageUpgrade);
	tag.putBool("overlockerUpgrade",overlockerUpgrade);
	tag.putBool("transformerUpgrade",transformerUpgrade);
	tag.putInt("directionType",(int)directionType);
	tag.putInt("moveType",(int)moveType);
}
void ICMachineBlockEntity::tick(Level&l,unsigned long long t)
{
	//ContainerBlockEntity::tick(l,t);
}
bool ICMachineBlockEntity::hasRedstoneInverterUpgrade()const
{
	return redstoneInverter;
}
bool ICMachineBlockEntity::hasEnergyStorageUpgrade()const
{
	return energyStorageUpgrade;
}
bool ICMachineBlockEntity::hasOverlockerUpgrade()const
{
	return overlockerUpgrade;
}
bool ICMachineBlockEntity::hasTransformerUpgrade()const
{
	return transformerUpgrade;
}
ICMachineBlockEntity::DirectionType ICMachineBlockEntity::getDirectionType()const
{
	return directionType;
}
ICMachineBlockEntity::MoveType ICMachineBlockEntity::getMoveType()const
{
	return moveType;
}
void ICMachineBlockEntity::setMoveType(MoveType t)
{
	moveType=t;
}
void ICMachineBlockEntity::setDirectionType(DirectionType t)
{
	directionType=t;
}
void ICMachineBlockEntity::setHasRedstoneInverterUpgrade(bool b)
{
	redstoneInverter=b;
}
void ICMachineBlockEntity::setHasEnergyStorageUpgrade(bool b)
{
	energyStorageUpgrade=b;
}
void ICMachineBlockEntity::setHasOverlockerUpgrade(bool b)
{
	overlockerUpgrade=b;
}
void ICMachineBlockEntity::setHasTransformerUpgrade(bool b)
{
	transformerUpgrade=b;
}
void ICMachineBlockEntity::use(ItemInstance&item)
{
	if(item.isNull())
		return;
	bool shouldCost=false;
	/*switch(item.getId())
	{
	case IC::Items::ID::mTransformer:
		shouldCost=true;
		setHasTransformerUpgrade(true);
		break;
	case IC::Items::ID::mRedstoneInverter:
		shouldCost=true;
		setHasRedstoneInverterUpgrade(true);
		break;
	case IC::Items::ID::mOverclocker:
		shouldCost=true;
		setHasOverlockerUpgrade(true);
		break;
	case IC::Items::ID::mEnergyStorage:
		shouldCost=true;
		setHasEnergyStorageUpgrade(true);
		break;
	}*/
	if(shouldCost)
		item.remove(1);
}
float ICMachineBlockEntity::getOverlockedSpeed(float f)const
{
	if(overlockerUpgrade)
		return f*1.5F;
	return f;
}
