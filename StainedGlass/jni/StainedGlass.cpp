

/*
  IMPORTANT: PLEASE READ MANIFEST FILE!
  assets/nmod_manifest.json
*/



#include <jni.h>
//jni.h provides the implementation of JavaVM*,JNIEnv*,JNIEXPORT,jobject,jstring,jnit and JNI_VERSION_1_6.
#include "Substrate.h"
//Substrate.h provided MSHookFunction.
//We can use MSHookFunction to edit methods in libminecraftpe.so
#include <string>
//headers in gnustl.
#include "mcpe/block/Block.h"
#include "mcpe/block/blocks/GlassBlock.h"
#include "mcpe/block/blocks/ThinFenceBlock.h"
#include "mcpe/block/BlockGraphics.h"
#include "mcpe/blockentity/BlockEntity.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/item/AuxDataBlockItem.h"
#include "mcpe/item/Item.h"
#include "mcpe/util/Color.h"
#include "mcpe/util/BlockPos.h"
#include "mcpe/util/Vec3.h"
#include "mcpe/client/resources/I18n.h"
//headers of mcpe.

//Define Blocks---------------------------------------------------------------

#define ID_STAINED_GLASS (241)

//create a class that extends Block.
//Stained Glass
class StainedGlassBlock : public GlassBlock
{
public:
	StainedGlassBlock(std::string const&name,int id):
	GlassBlock(name,id,Material::getMaterial(MaterialType::GLASS),true)
	//Material:Glass
	{
		//set render layer to slime block's.
		(*((int*)(((void*)this)+20))) = (*((int*)(((void*)Block::mSlimeBlock)+20)));
		setCategory(CreativeItemCategory::DECORATIONS);
		setSolid(false);
	}
public:
	//Description Name of the Block.
	//Aux:Block Data.
	virtual std::string buildDescriptionName(unsigned char aux) const
	{
		switch(aux)
		{
		case 0:
			return I18n::get("tile.stained_glass.white.name");
		case 1:
			return I18n::get("tile.stained_glass.orange.name");
		case 2:
			return I18n::get("tile.stained_glass.magenta.name");
		case 3:
			return I18n::get("tile.stained_glass.lightBlue.name");
		case 4:
			return I18n::get("tile.stained_glass.yellow.name");
		case 5:
			return I18n::get("tile.stained_glass.lime.name");
		case 6:
			return I18n::get("tile.stained_glass.pink.name");
		case 7:
			return I18n::get("tile.stained_glass.gray.name");
		case 8:
			return I18n::get("tile.stained_glass.silver.name");
		case 9:
			return I18n::get("tile.stained_glass.cyan.name");
		case 10:
			return I18n::get("tile.stained_glass.purple.name");
		case 11:
			return I18n::get("tile.stained_glass.blue.name");
		case 12:
			return I18n::get("tile.stained_glass.brown.name");
		case 13:
			return I18n::get("tile.stained_glass.green.name");
		case 14:
			return I18n::get("tile.stained_glass.red.name");
		case 15:
			return I18n::get("tile.stained_glass.black.name");
		}
		return "stained_glass";
	}
	//Returns ItemInstance that will be dropped by silk touch tools.
	//Aux:Block Data.
	virtual ItemInstance getSilkTouchItemInstance(unsigned char aux) const
	{
		return ItemInstance(ID_STAINED_GLASS,1,getSpawnResourcesAuxValue(aux));
	}
	//Returns Item Data that will be dropped.
	//Aux:Block Data.
	virtual int getSpawnResourcesAuxValue(unsigned char aux) const
	{
		return aux;
	}
	// render layer of Block.
	virtual int getRenderLayer(BlockSource&region, BlockPos const&pos) const
	{
		//use slime block's render layer.
		return mSlimeBlock->getRenderLayer(region,pos);
	}
};

//Invoked when the game is registering Blocks.
void (*block_initBlocks_)(); //Pointer of method Block::initBlocks.
void block_initBlocks()  //Replace method.
{
	//invoke default method.
	//Warning: DO NOT invoke Block::initBlocks!The program will be in a loop forever!
	//Warning: You must invoke default method in this situation.If not,game will crash.
	//Some Replace method do not to invoke default method.That depends different situations.
	block_initBlocks_();
	
	//register our own Blocks:
	//To register a block,we should define a Block instance.
	
	Block::mBlocks[ID_STAINED_GLASS] = Block::mStainedGlass = new StainedGlassBlock("stained_glass",ID_STAINED_GLASS);
	
	//add blocks to mBlockLookupMap so that the blocks can be found by game.
	Block::mBlockLookupMap.emplace("stained_glass",Block::mBlocks[ID_STAINED_GLASS]);
}

//Invoked when the game is registering Block Graphics.
void (*blockGraphics_initBlocks_)(ResourcePackManager&);
void blockGraphics_initBlocks(ResourcePackManager&m)
{
	blockGraphics_initBlocks_(m);
	
	//register our own BlockGraphics:
	//To register a block,we should also define BlockGraphics.
	
	BlockGraphics::mBlocks[ID_STAINED_GLASS] = new BlockGraphics("stained_glass");
	//we use portal so that the block will be transparent.
	BlockGraphics::mBlocks[ID_STAINED_GLASS] -> setTextureItem("stained_glass");
	//Set texture of stained glass.
	BlockGraphics::mBlocks[ID_STAINED_GLASS] -> setSoundType(BlockSoundType::GLASS);
	//Set sound type of stained glass.
	
	//Texture Data defined in : assets/resource_packs/vanilla/textures/terrain_textures.json
}

// we define stained glass items here.
void initStainedGlassItems()
{
	//register our own Block Items:
	//To register a block,we should also define BlockItem.
	
	Item::mItems[ID_STAINED_GLASS] = new AuxDataBlockItem("stained_glass",
	ID_STAINED_GLASS - 0x100, //0x100 , same as 256, must be cost in the conductor.
	Block::mBlocks[ID_STAINED_GLASS] );
	
	Item::mItems[ID_STAINED_GLASS] -> setCategory(CreativeItemCategory::DECORATIONS);
	
	Item::mItemLookupMap.emplace("stained_glass",std::pair<std::string const,std::unique_ptr<Item>>("stained_glass",std::unique_ptr<Item>(Item::mItems[ID_STAINED_GLASS])));
	
	//We use AuxDataBlockItem to make sure the block is aux dataed.
	//If the block we defined don't need to be aux dataed,we can use BlockItem instead.
	
}

//Invoked when the game is registering Creative Mode Inventory Items.
void (*item_initCreativeItems_)();
void item_initCreativeItems()
{
	item_initCreativeItems_();
	
	//add our block items to creative mode inventory.
	
	for(size_t index=0; index<16; ++index)
		Item::addCreativeItem(ID_STAINED_GLASS,index);
}

//Inviked when the game is defining items.
void (*item_registerItems_)();
void item_registerItems()
{
	item_registerItems_();
	
	initStainedGlassItems();
}

//Colorful Beacon -------------------------------------------------------------

//BeaconRenderer
namespace mce
{
	class TexturePtr;
	class MaterialPtr;
	class TextureGroup;
}
class Tessellator;
class BeaconRenderer
// : public EntityShaderManager
// , public BlockEntityRenderer
{
public:
	virtual ~BeaconRenderer();
	virtual void render(BlockSource&, BlockEntity&, Vec3 const&, unsigned char, float, mce::MaterialPtr const&, mce::TexturePtr const&, int);
	virtual void renderAlpha(BlockSource&, BlockEntity&, Vec3 const&, unsigned char, float, mce::MaterialPtr const&, mce::TexturePtr const&, int);
public:
	BeaconRenderer(mce::TextureGroup&);
	void tessellateAlphaBeamSegment(Tessellator&, Vec3 const&, float, Color const&, float);
	void tessellateOpaqueBeamSegment(Tessellator&, Vec3 const&, float, Color const&, float);
public:
	static float const SCROLL_SPEED;
	static float const ROTATION_SPEED;
	static float const BEAM_GLOW_RADIUS;
	static float const SOLID_BEAM_RADIUS;
};

Color beaconColors[256];
Color beaconColorsAlpha[256];

Color getBeaconColorType(int aux)
{
	switch(aux)
	{
	case 0:
		return Color((float)256/256,(float)256/256,(float)256/256,0.15F);
	case 1:
		return Color((float)215/256,(float)128/256,(float)50/256,0.15F);
	case 2:
		return Color((float)178/256,(float)75/256,(float)215/256,0.15F);
	case 3:
		return Color((float)103/256,(float)153/256,(float)215/256,0.15F);
	case 4:
		return Color((float)230/256,(float)230/256,(float)50/256,0.15F);
	case 5:
		return Color((float)128/256,(float)205/256,(float)25/256,0.15F);
	case 6:
		return Color((float)243/256,(float)168/256,(float)125/256,0.15F);
	case 7:
		return Color((float)75/256,(float)75/256,(float)75/256,0.15F);
	case 8:
		return Color((float)154/256,(float)154/256,(float)154/256,0.15F);
	case 9:
		return Color((float)75/256,(float)128/256,(float)153/256,0.15F);
	case 10:
		return Color((float)128/256,(float)63/256,(float)178/256,0.15F);
	case 11:
		return Color((float)50/256,(float)75/256,(float)178/256,0.15F);
	case 12:
		return Color((float)103/256,(float)75/256,(float)50/256,0.15F);
	case 13:
		return Color((float)103/256,(float)128/256,(float)50/256,0.15F);
	case 14:
		return Color((float)153/256,(float)50/256,(float)50/256,0.15F);
	case 15:
		return Color((float)0/256,(float)0/256,(float)0/256,0.15F);
	}
	return Color::NIL;
}

//render beacon beam segment
void (*renderBeacon_)(BeaconRenderer*,BlockSource&, BlockEntity&, Vec3 const&, unsigned char, float, mce::MaterialPtr const&, mce::TexturePtr const&, int);
void renderBeacon(BeaconRenderer*self,BlockSource&region, BlockEntity&blockentity, Vec3 const&position, unsigned char uch, float f, mce::MaterialPtr const&materialPtr, mce::TexturePtr const&texturePtr, int i)
{
	//prepare colors and save into beaconColors array.
	for(Color& color:beaconColors)
		color=Color::NIL;
	
	int xPos=blockentity.getPosition().x;
	int yPos=blockentity.getPosition().y;
	int zPos=blockentity.getPosition().z;
	
	Color cacheColorType=Color::NIL;
	for(size_t index=yPos; index<256; ++index)
	{
		if(region.getBlock(xPos,index,zPos)==Block::mStainedGlass)
		{
			beaconColors[index]=cacheColorType=getBeaconColorType(region.getData(xPos,index,zPos));
		}
		else
			beaconColors[index]=cacheColorType;
	}
	
	renderBeacon_(self,region,blockentity,position,uch,f,materialPtr,texturePtr,i);
	
	for(Color& color:beaconColors)
		color=Color::NIL;
}

void (*renderBeaconAlpha_)(BeaconRenderer*,BlockSource&, BlockEntity&, Vec3 const&, unsigned char, float, mce::MaterialPtr const&, mce::TexturePtr const&, int);
void renderBeaconAlpha(BeaconRenderer*self,BlockSource&region, BlockEntity&blockentity, Vec3 const&position, unsigned char uch, float f, mce::MaterialPtr const&materialPtr, mce::TexturePtr const&texturePtr, int i)
{
	//prepare colors and save into beaconColors array.
	for(Color& color:beaconColorsAlpha)
		color=Color::NIL;
	
	int xPos=blockentity.getPosition().x;
	int yPos=blockentity.getPosition().y;
	int zPos=blockentity.getPosition().z;
	
	Color cacheColorType=Color::NIL;
	for(size_t index=yPos; index<256; ++index)
	{
		if(region.getBlock(xPos,index,zPos)==Block::mStainedGlass)
		{
			beaconColorsAlpha[index]=cacheColorType=getBeaconColorType(region.getData(xPos,index,zPos));
		}
		else
			beaconColorsAlpha[index]=cacheColorType;
	}
	
	renderBeaconAlpha_(self,region,blockentity,position,uch,f,materialPtr,texturePtr,i);
	
	for(Color& color:beaconColorsAlpha)
		color=Color::NIL;
}


void (*tessellateAlphaBeamSegment_)(Tessellator&, Vec3 const&, float, Color const&, float);
void tessellateAlphaBeamSegment(Tessellator&tessellator, Vec3 const&pos, float f, Color const&color, float f2)
{
	//tessellate colored beam segment
	int yPosition=255;
	if(beaconColorsAlpha[yPosition]==Color::NIL)
		tessellateAlphaBeamSegment_(tessellator,pos,f,color,f2);
	else
		tessellateAlphaBeamSegment_(tessellator,pos,f,beaconColorsAlpha[yPosition],f2);
}

void (*tessellateOpaqueBeamSegment_)(Tessellator&, Vec3 const&, float, Color const&, float);
void tessellateOpaqueBeamSegment(Tessellator&tessellator, Vec3 const&pos, float f, Color const&color, float f2)
{
	//tessellate colored beam segment
	int yPosition=255;
	if(beaconColors[yPosition]==Color::NIL)
		tessellateOpaqueBeamSegment_(tessellator,pos,f,color,f2);
	else
		tessellateOpaqueBeamSegment_(tessellator,pos,f,beaconColors[yPosition],f2);
}
//Config area------------------------------------------------------------------

//You must use extern "C" so that NMod_onLoad , NMod_onActivityCreate , NMod_onActivityFinish can be found and invoked.
extern "C"
{
	//NMod_onLoad , NMod_onActivityCreate , NMod_onActivityFinish are methods that provided by ModdedPE.
	//You don't need to implement them all.
	
	void NMod_onLoad(JavaVM*jvm,JNIEnv* env,std::string const& mcVersionName,std::string const& moddedpeVersionName)
	{
		//NMod_onLoad is invoked when the *.so file is loaded.(later than JNI_OnLoad).
		//You can use MSHookFunction here or JNI_OnLoad.
		//Warning:DO NOT use MSHookFunction in JNI_OnLoad and NMod_onLoad at the same time!
		
		MSHookFunction(
		(void*)& Block::initBlocks, //Default Method in libminecraftpe.so,will be replaced by block_initBlocks
		(void*)& block_initBlocks, //Replace Method that implements by us,will replace Block::initBlocks
		(void**)& block_initBlocks_); //Pointer of default method which will be replaced.If we want to invoke Block::initBlocks,use block_initBlocks_ instead.
		//Warning:You must use (void**)& instead of (void*)& to cast pointer methods!
		//Warning:You must use (void*)& instead of (void**)& to cast methods!
		
		//Other MSHookFunction
		MSHookFunction( (void*)&BlockGraphics::initBlocks, (void*)&blockGraphics_initBlocks, (void**)&blockGraphics_initBlocks_);
		MSHookFunction( (void*)&Item::initCreativeItems, (void*)&item_initCreativeItems, (void**)&item_initCreativeItems_);
		MSHookFunction( (void*)&Item::registerItems, (void*)&item_registerItems, (void**)&item_registerItems_);
		MSHookFunction( (void*)&BeaconRenderer::render, (void*)&renderBeacon, (void**)&renderBeacon_);
		MSHookFunction( (void*)&BeaconRenderer::renderAlpha, (void*)&renderBeaconAlpha, (void**)&renderBeaconAlpha_);
		MSHookFunction( (void*)&BeaconRenderer::tessellateAlphaBeamSegment, (void*)&tessellateAlphaBeamSegment, (void**)&tessellateAlphaBeamSegment_);
		MSHookFunction( (void*)&BeaconRenderer::tessellateOpaqueBeamSegment, (void*)&tessellateOpaqueBeamSegment, (void**)&tessellateOpaqueBeamSegment_);
	}

	void NMod_onActivityCreate(JNIEnv*env,jobject mainActivity,jobject savedInstanceState)
	{
		//mainActivity is a java object of MainActivity (com.mojang.minecraftpe.MainActivity)
		//savedInstanceState is a java object of Bundle that provided by MainActivity.onCreate(Bundle savedInstanceState)
		
	}

	void NMod_onActivityFinish(JNIEnv*env,jobject mainActivity)
	{
		//mainActivity is a java object of MainActivity (com.mojang.minecraftpe.MainActivity)
		
	}
	
	//JNI_OnLoad Method.
	//When the *.so is loaded,it will be invoked.
	//Please return JNI_VERSION_1_6 in it.
	
	JNIEXPORT jint JNI_OnLoad(JavaVM*,void*)
	{
		return JNI_VERSION_1_6;
	}
}
