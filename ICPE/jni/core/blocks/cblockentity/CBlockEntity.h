#pragma once

#include "mcpe/blockentity/BlockEntity.h"
#include "mcpe/util/DimensionId.h"
#include "mca/data/Database.h"

class CBlockEntity : public BlockEntity
{
private:
	DimensionId dimID;
	mca::Database database;
	bool createdDatabase;
	short blockId;
	bool autoDelete;
public:
	CBlockEntity(BlockPos const&);
public:
	virtual void onMove();
	virtual void save(CompoundTag&)const;
	virtual void tick(BlockSource&);
	virtual void onPlace(BlockSource&);
public:
	virtual void save(mca::CompoundTag&)const;
	virtual void load(mca::CompoundTag const&);
public:
	void setNotAutoDelete();
private:
	void onSave();
};
