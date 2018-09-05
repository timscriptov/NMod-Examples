#include "CBlockEntity.h"

#include "CBlockEntityAPI.h"
#include "CBlockEntityManager.h"

#include "mcpe/level/BlockSource.h"
#include "mcpe/util/BlockPos.h"
#include "mcpe/util/Util.h"
#include "mcpe/util/BlockID.h"

#include <fstream>

CBlockEntity::CBlockEntity(BlockPos const&pos):BlockEntity((BlockEntityType)100,pos,"CBlock")
{
	createdDatabase=false;
	blockId=-1;
	autoDelete=true;
}
void CBlockEntity::save(CompoundTag&tag)const
{
	BlockEntity::save(tag);
	
	((CBlockEntity*)this)->onSave();
}
void CBlockEntity::onSave()
{
	mca::CompoundTag & tag_=database.getTag(CBlockEntityAPI::manager.getPathFor(getPosition(),dimID));
	save(tag_);
	database.save();
}
void CBlockEntity::onPlace(BlockSource&s)
{
	BlockEntity::onPlace(s);
	
	dimID=s.getDimensionId();
	
	if(!createdDatabase&&autoDelete)
	{
		std::ofstream ofs(CBlockEntityAPI::manager.getPathFor(getPosition(),dimID));
		ofs<<"";
	}
	if(!createdDatabase)
	{
		std::string path=CBlockEntityAPI::manager.getPathFor(getPosition(),dimID);
		database=mca::Database(path,Util::toString(blockId=s.getBlockID(getPosition()).id),getPosition().x^getPosition().y^getPosition().z);
		load(database.getTag(path));
		save(database.getTag(path));
		createdDatabase=true;
	}
}
void CBlockEntity::setNotAutoDelete()
{
	autoDelete=false;
}
void CBlockEntity::onMove()
{
	BlockEntity::onMove();
	
	if(blockId>=0)
	{
		std::string path=CBlockEntityAPI::manager.getPathFor(getPosition(),dimID);
		database=mca::Database(path,Util::toString(blockId),getPosition().x^getPosition().y^getPosition().z);
		save(database.getTag(path));
	}
}
void CBlockEntity::save(mca::CompoundTag&)const
{
	
}
void CBlockEntity::tick(BlockSource&s)
{
	BlockEntity::tick(s);
	setChanged();
	dimID=s.getDimensionId();
	
	if(!createdDatabase&&autoDelete)
	{
		std::ofstream ofs(CBlockEntityAPI::manager.getPathFor(getPosition(),dimID));
		ofs<<"";
	}
	if(!createdDatabase)
	{
		std::string path=CBlockEntityAPI::manager.getPathFor(getPosition(),dimID);
		database=mca::Database(path,Util::toString(blockId=s.getBlockID(getPosition()).id),getPosition().x^getPosition().y^getPosition().z);
		load(database.getTag(path));
		save(database.getTag(path));
		createdDatabase=true;
	}
}
void CBlockEntity::load(mca::CompoundTag const&)
{
	
}
