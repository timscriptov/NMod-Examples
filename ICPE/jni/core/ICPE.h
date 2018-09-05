#pragma once

#include <jni.h>
#include <string>
#include <memory>

class Localization;
class Level;
class Player;
class Recipes;
class LevelChunk;
class BlockTessellator;
class MinecraftGame;
class Minecraft;
class Block;
class Item;
class BlockPos;
class LevelSettings;
class ResourcePackManager;
class BlockGraphics;
class ClientInstance;
class UIScreenChooser;
class Random;
class BiomeDecorator;
class ItemInstance;
class Biome;
class BlockSource;
class Dimension;
class CompoundTag;
class FlowerPotBlock;
class Enchant;
class Entity;
class UIControl;
class RectangleArea;
class RendererStack;
class SoundManager;
class MinecraftInputHandler;
typedef unsigned char uchar;

class ICPE
{
public:
	static void launch(JavaVM*);
	static void setupMSHookFunctions();
public:
	static void (*decorateChunk_)(BiomeDecorator*,BlockSource*, Random&, Biome*, BlockPos const&, bool, float);
	static void decorateChunk(BiomeDecorator*,BlockSource*, Random&, Biome*, BlockPos const&, bool, float);
	static void (*initRecipes_)(Recipes*);
	static void initRecipes(Recipes*);
	static bool (*tessellateInWorld_)(BlockTessellator*,Block const&,BlockPos const&,uchar,bool);
	static bool tessellateInWorld(BlockTessellator*,Block const&,BlockPos const&,uchar,bool);
	static void (*initGame_)(MinecraftGame*);
	static void initGame(MinecraftGame*);
	static void (*initCreativeItems_)();
	static void initCreativeItems();
	static void (*teardownItems_)();
	static void teardownItems();
	static bool (*isSupportedFlower_)(FlowerPotBlock const*const,Block const*,int);
	static bool isSupportedFlower(FlowerPotBlock const*const,Block const*,int);
	static void (*initItems_)();
	static void initItems();
	static void (*initItemsServer_)(ResourcePackManager&);
	static void initItemsServer(ResourcePackManager&);
	static void (*initBlockGraphics_)(ResourcePackManager&);
	static void initBlockGraphics(ResourcePackManager&);
	static void (*initBlocks_)();
	static void initBlocks();
	static void (*teardownBlocks_)();
	static void teardownBlocks();
	static void (*tickLevel_)(Level*);
	static void tickLevel(Level*);
	static bool (*isAnyAuxValue_)(int);
	static bool isAnyAuxValue(int);
	static void (*renderHotBar_)(void*,ClientInstance&,UIControl&,int,RectangleArea&);
	static void renderHotBar(void*,ClientInstance&,UIControl&,int,RectangleArea&);
public:
	static MinecraftGame* pMinecraftGame;
	static Level* pLevel;
	static UIScreenChooser mUIScreenChooser;
	static RendererStack mRendererStack;
	static Random mRandom;
	static SoundManager soundManager;
	static const int localKeyCode;
	static JavaVM* jvm;
	static std::string externalStorageDirectory;
};
