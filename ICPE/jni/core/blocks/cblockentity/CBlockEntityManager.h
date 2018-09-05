#pragma once

#include <string>
#include <thread>
#include <memory>
#include "mca/data/Database.h"
#include "mcpe/util/DimensionId.h"

class CEntityBlock;
class BlockPos;
class LevelChunk;
class BlockEntity;
class CBlockEntity;
class BlockSource;
class BlockPos;

class CBlockEntityManager
{
private:
	std::string filePath;
public:
	CBlockEntityManager(std::string const&path="");
	~CBlockEntityManager();
public:
	std::string getPathFor(BlockPos const&,DimensionId);
	void loadAll(LevelChunk&,BlockSource&);
	std::unique_ptr<CBlockEntity> createBlockEntity(CEntityBlock*,BlockPos const&);
};
