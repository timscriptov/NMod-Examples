#pragma once

#include "ICBlockEntity.h"

#include "util/energy/Energy.h"
#include "mcpe/entity/PaletteColor.h"

class CableBlockEntity : public ICBlockEntity
{
private:
	unsigned short colorType;
	unsigned long long lastTick;
	unsigned long lastPower;
	unsigned int lastVoltage;
	unsigned long power;
	unsigned int voltage;
	bool shouldUpdateNeighbors;
public:
	CableBlockEntity(BlockPos const&);
	~CableBlockEntity()=default;
public:
	virtual void tick(BlockSource&);
	virtual void load(mca::CompoundTag const&);
	virtual void save(mca::CompoundTag &)const;
	virtual bool isEnergyConductor()const;
public:
	unsigned char getColor()const;
	void setColor(unsigned char);
	unsigned char getTextureAux(unsigned char)const;
	void addVoltage(unsigned int);
	void addPower(unsigned long);
	Energy getEnergyConducted()const;
};
