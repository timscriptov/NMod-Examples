#include "CBlockEntityAPI.h"

#include "CBlockEntityManager.h"
#include "CBlockEntity.h"

#include "Substrate.h"

#include "mcpe/block/Block.h"
#include "mcpe/blockentity/BlockEntity.h"
#include "mcpe/blockentity/BlockEntityFactory.h"
#include "mcpe/util/Util.h"
#include "mcpe/nbt/CompoundTag.h"
#include "mcpe/client/ClientInstance.h"
#include "mcpe/client/MinecraftGame.h"
#include "mcpe/client/resources/FilePathManager.h"
#include "mcpe/client/gui/GuiData.h"
#include "mcpe/client/Minecraft.h"
#include "mcpe/entity/player/Player.h"
#include "mcpe/util/ChunkPos.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/level/Level.h"
#include "mcpe/level/chunk/LevelChunk.h"

ClientInstance* CBlockEntityAPI::client;
CBlockEntityManager CBlockEntityAPI::manager;
void CBlockEntityAPI::setup()
{
	MSHookFunction((void*)&ClientInstance::init,(void*)&initClient,(void**)&initClient_);
	MSHookFunction((void*)(BlockEntity* (BlockSource::*)(int,int,int))&BlockSource::getBlockEntity,(void*)&getBlockEntity_iii,(void**)&getBlockEntity_iii_);
	MSHookFunction((void*)(BlockEntity* (BlockSource::*)(BlockPos const&))&BlockSource::getBlockEntity,(void*)&getBlockEntity_rkbp,(void**)&getBlockEntity_rkbp_);
	MSHookFunction((void*)&Minecraft::createLevel,(void*)&createLevel,(void**)&createLevel_);
	MSHookFunction((void*)&BlockEntityFactory::createBlockEntity,(void*)&bef_createBlockEntity,(void**)&bef_createBlockEntity_);
	MSHookFunction((void*)&LevelChunk::onLoaded,(void*)&onChunkLoaded,(void**)&onChunkLoaded_);
	MSHookFunction((void*)&BlockEntity::initBlockEntities,(void*)&initBlockEntities,(void**)&initBlockEntities_);
}
BlockEntity* (*CBlockEntityAPI::getBlockEntity_iii_)(BlockSource*,int,int,int);
BlockEntity* CBlockEntityAPI::getBlockEntity_iii(BlockSource*s,int x,int y,int z)
{
	BlockEntity* ret=getBlockEntity_iii_(s,x,y,z);
	Block* self_block=0;
	
	if(!ret)
	{
		self_block=s->getBlock(x,y,z);
		if(isCEntityBlock(*self_block))
		{
			CEntityBlock* ceb=(CEntityBlock*) s->getBlock(x,y,z);
			std::unique_ptr<CBlockEntity> be=manager.createBlockEntity(ceb,BlockPos(x,y,z));
			be->setNotAutoDelete();
			LevelChunk* c=s->getChunkAt(x,y,z);
			if(c)
				c->_placeBlockEntity(std::move(be));
			else
				return be.get();
			return getBlockEntity_iii_(s,x,y,z);
		}
	}
	
	return ret;
}
BlockEntity* (*CBlockEntityAPI::getBlockEntity_rkbp_)(BlockSource*,BlockPos const&);
BlockEntity* CBlockEntityAPI::getBlockEntity_rkbp(BlockSource*s,BlockPos const&pos)
{
	BlockEntity* ret=getBlockEntity_rkbp_(s,pos);
	Block* self_block=0;
	
	if(!ret)
	{
		self_block=s->getBlock(pos);
		if(isCEntityBlock(*self_block))
		{
			CEntityBlock* ceb=(CEntityBlock*) s->getBlock(pos);
			std::unique_ptr<CBlockEntity> be=manager.createBlockEntity(ceb,pos);
			be->setNotAutoDelete();
			LevelChunk* c=s->getChunkAt(pos);
			if(c)
				c->_placeBlockEntity(std::move(be));
			else
				return be.get();
			return getBlockEntity_rkbp_(s,pos);
		}
	}
	
	return ret;
}
void (*CBlockEntityAPI::initClient_)(ClientInstance*);
void CBlockEntityAPI::initClient(ClientInstance*self)
{
	initClient_(self);
	client=self;
}
void (*CBlockEntityAPI::createLevel_)(Minecraft*,void*,std::string const&,std::string const&,std::string const&,std::string const&,LevelSettings const&,ResourcePackManager&);
void CBlockEntityAPI::createLevel(Minecraft*m,void*v,std::string const&path,std::string const&name,std::string const&s1,std::string const&s2,LevelSettings const&set,ResourcePackManager&mgr)
{
	createLevel_(m,v,path,name,s1,s2,set,mgr);
	
	if(client)
		manager=CBlockEntityManager(client->getMinecraftGame()->getFilePathManager()->getWorldsPath()+"/"+path+"/db/mcacbe");
}
std::unique_ptr<BlockEntity> (*CBlockEntityAPI::bef_createBlockEntity_)(BlockEntityType t, BlockPos const&pos, BlockID);
std::unique_ptr<BlockEntity> CBlockEntityAPI::bef_createBlockEntity(BlockEntityType t, BlockPos const&pos, BlockID id)
{
	if(((int)Block::mBlocks[id.id]->getBlockEntityType())==100)
	{
		CEntityBlock* ceb=(CEntityBlock*) Block::mBlocks[id.id];
		std::unique_ptr<BlockEntity> be=manager.createBlockEntity(ceb,pos);
		if(be.get())
			return be;
	}
	return bef_createBlockEntity_(t,pos,id);
}
void (*CBlockEntityAPI::initBlockEntities_)();
void CBlockEntityAPI::initBlockEntities()
{
	initBlockEntities_();
	
	BlockEntity::setId((BlockEntityType)100,"CBlock");
}
void (*CBlockEntityAPI::onChunkLoaded_)(LevelChunk*c,BlockSource&);
void CBlockEntityAPI::onChunkLoaded(LevelChunk*c,BlockSource&s)
{
	onChunkLoaded_(c,s);
	
	manager.loadAll(*c,s);
}
bool CBlockEntityAPI::isCEntityBlock(Block const&b)
{
	return ((int)b.getBlockEntityType())==100;
}
