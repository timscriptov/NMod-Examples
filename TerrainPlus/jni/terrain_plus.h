#pragma once
#include <string>

class MinecraftGame;
class ClientInstance;
class UIControl;
class RectangleArea;
class SidebarManager;
class Player;
class ItemInstance;
class Biome;
class Entity;

class TerrainPlus
{
private:
	static MinecraftGame* mMinecraftGame;
	static Biome* mTargetBiome;
public:
	static void (*initMinecraftGame_)(MinecraftGame*);
	static void initMinecraftGame(MinecraftGame*);
	static void (*onPlayerLoaded_)(MinecraftGame*,Player&);
	static void onPlayerLoaded(MinecraftGame*,Player&);
	static void (*renderGamePlay_)(void*,ClientInstance&,UIControl&,int,RectangleArea&);
	static void renderGamePlay(void*,ClientInstance&,UIControl&,int,RectangleArea&);
	static bool (*useItem_)(ItemInstance*,Player&);
	static bool useItem(ItemInstance*,Player&);
	static bool (*useOn_)(ItemInstance*,Entity&, int, int, int, signed char, float, float, float);
	static bool useOn(ItemInstance*,Entity&, int, int, int, signed char, float, float, float);
public:
	static bool isEditing;
	static SidebarManager mSidebarManager;
};
