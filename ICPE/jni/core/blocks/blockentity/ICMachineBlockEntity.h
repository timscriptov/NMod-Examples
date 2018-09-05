#pragma once

#include "ContainerBlockEntity.h"
#include "util/energy/Energy.h"
#include "util/energy/EnergyWeb.h"

class ICMachineBlockEntity : public ContainerBlockEntity
{
public:
	enum class DirectionType : int
	{
		NONE,
		ALL,
		UP,
		DOWN,
		WEST,
		EAST,
		NORTH,
		SOUTH
	};
	enum class MoveType : int
	{
		NONE,
		FLUID_PULLING,
		FLUID_EJECTOR,
		PULLING,
		EJECTOR
	};
protected:
	bool redstoneInverter;
	bool energyStorageUpgrade;
	bool overlockerUpgrade;
	bool transformerUpgrade;
	DirectionType directionType;
	MoveType moveType;
public:
	ICMachineBlockEntity(BlockPos const&,int);
	~ICMachineBlockEntity()=default;
public:
	virtual void load(mca::CompoundTag const&);
	virtual void save(mca::CompoundTag &)const;
	virtual void tick(Level&,unsigned long long);
	virtual bool isMachine()const;
public:
	bool hasRedstoneInverterUpgrade()const;
	bool hasEnergyStorageUpgrade()const;
	bool hasOverlockerUpgrade()const;
	bool hasTransformerUpgrade()const;
	DirectionType getDirectionType()const;
	MoveType getMoveType()const;
	void setMoveType(MoveType);
	void explode();
	void setDirectionType(DirectionType);
	void setHasRedstoneInverterUpgrade(bool);
	void setHasEnergyStorageUpgrade(bool);
	void setHasOverlockerUpgrade(bool);
	void setHasTransformerUpgrade(bool);
	void use(ItemInstance&);
	float getOverlockedSpeed(float)const;
};
