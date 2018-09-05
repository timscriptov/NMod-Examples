#include "CBlockEntityManager.h"

#include "CEntityBlock.h"
#include "CBlockEntity.h"
#include "mcpe/util/Util.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/util/ChunkPos.h"
#include "mcpe/level/chunk/LevelChunk.h"
#include "mcpe/block/Block.h"

CBlockEntityManager::CBlockEntityManager(std::string const&path)
{
	filePath=path;
}
CBlockEntityManager::~CBlockEntityManager()
{
	
}
std::string CBlockEntityManager::getPathFor(BlockPos const&pos,DimensionId id)
{
	std::string key=filePath+"/"+"mcacbe_"+Util::toString(pos.x)+"-"+Util::toString(pos.y)+"-"+Util::toString(pos.z)+"-"+Util::toString((int)id)+".mcadb";
	return key;
}
void CBlockEntityManager::loadAll(LevelChunk&c,BlockSource&s)
{
	ChunkPos base_pos=c.getPosition();
	
	for(int x=base_pos.x*16;x<base_pos.x*16+16;++x)
	{
		for(int z=base_pos.z*16;z<base_pos.z*16+16;++z)
		{
			for(int y=0;y<256;++y)
			{
				if(((int)s.getBlock(x,y,z)->getBlockEntityType())==100)
				{
					CEntityBlock* ceb=(CEntityBlock*) s.getBlock(x,y,z);
					std::unique_ptr<CBlockEntity> be=createBlockEntity(ceb,BlockPos(x,y,z));
					be->setNotAutoDelete();
					c._placeBlockEntity(std::move(be));
				}
			}
		}
	}
}
std::unique_ptr<CBlockEntity> CBlockEntityManager::createBlockEntity(CEntityBlock*b,BlockPos const&pos)
{
	std::unique_ptr<CBlockEntity> be = b->createBlockEntity(pos);
	return be;
}
