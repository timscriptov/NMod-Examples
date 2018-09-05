#pragma once

#include <string>
#include <memory>

#include "mcpe/blockentity/BlockEntityType.h"

class CBlockEntityManager;
class Minecraft;
class BlockPos;
class LevelChunk;
class BlockEntity;
class BlockSource;
class BlockEntityFactory;
class ChunkBlockPos;
class BlockID;
class ResourcePackManager;
class Block;
class LevelSettings;
class MinecraftGame;
class ClientInstance;

class CBlockEntityAPI
{
public:
	static ClientInstance* client;
	static CBlockEntityManager manager;
public:
	static void setup();
	static void (*initClient_)(ClientInstance*);
	static void initClient(ClientInstance*);
	static void (*createLevel_)(Minecraft*,void*,std::string const&,std::string const&,std::string const&,std::string const&,LevelSettings const&,ResourcePackManager&);
	static void createLevel(Minecraft*,void*,std::string const&,std::string const&,std::string const&,std::string const&,LevelSettings const&,ResourcePackManager&);
	static std::unique_ptr<BlockEntity> (*bef_createBlockEntity_)(BlockEntityType t, BlockPos const&pos, BlockID);
	static std::unique_ptr<BlockEntity> bef_createBlockEntity(BlockEntityType t, BlockPos const&pos, BlockID);
	static void (*initBlockEntities_)();
	static void initBlockEntities();
	static BlockEntity* (*getBlockEntity_iii_)(BlockSource*,int,int,int);
	static BlockEntity* getBlockEntity_iii(BlockSource*,int,int,int);
	static BlockEntity* (*getBlockEntity_rkbp_)(BlockSource*,BlockPos const&);
	static BlockEntity* getBlockEntity_rkbp(BlockSource*,BlockPos const&);
	static void (*onChunkLoaded_)(LevelChunk*c,BlockSource&);
	static void onChunkLoaded(LevelChunk*c,BlockSource&s);
public:
	static bool isCEntityBlock(Block const&);
};
