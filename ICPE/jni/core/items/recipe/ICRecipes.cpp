#include "ICRecipes.h"

#include "blocks/Blocks.h"
#include "items/Items.h"
#include "MaceratorRecipes.h"
#include "ExtractorRecipes.h"
#include "CompressorRecipes.h"

ICRecipes::ICRecipes(Recipes&r,FurnaceRecipes&fr):ru(RecipeUtil(&r,&fr))
{
	MaceratorRecipes::initInstance();
	ExtractorRecipes::initInstance();
	CompressorRecipes::initInstance();
}
void ICRecipes::addRecipes()
{
	/*addItemRecipes();
	addFurnaceRecipes();
	addMaceratorRecipes();
	addExtractorRecipes();
	addCompressorRecipes();*/
}
void ICRecipes::addItemRecipes()
{
	using namespace IC;
#if 0
	//Painter empty
	addShapedRecipe(ItemInstance(Items::ID::mPainter,2,0),{
	"aab",
	" b ",
	" b "},{{'a',35,-1},{'b',280,-1}});
	//Painter red
	addShapelessRecipe(ItemInstance(Items::ID::mPainterRed,1,0),
	{{Items::ID::mPainter,-1},{351,1}});
	//Painter brown
	addShapelessRecipe(ItemInstance(Items::ID::mPainterBrown,1,0),
	{{Items::ID::mPainter,-1},{351,3}});
	//Painter Green
	addShapelessRecipe(ItemInstance(Items::ID::mPainterGreen,1,0),
	{{Items::ID::mPainter,-1},{351,2}});
	//Painter blue
	addShapelessRecipe(ItemInstance(Items::ID::mPainterBlue,1,0),
	{{Items::ID::mPainter,-1},{351,4}});
	//Painter magenta
	addShapelessRecipe(ItemInstance(Items::ID::mPainterMagenta,1,0),
	{{Items::ID::mPainter,-1},{351,13}});
	//Painter Purple
	addShapelessRecipe(ItemInstance(Items::ID::mPainterPurple,1,0),
	{{Items::ID::mPainter,-1},{351,5}});
	//Painter light blue
	addShapelessRecipe(ItemInstance(Items::ID::mPainterLightBlue,1,0),
	{{Items::ID::mPainter,-1},{351,12}});
	//Painter white
	addShapelessRecipe(ItemInstance(Items::ID::mPainterWhite,1,0),
	{{Items::ID::mPainter,-1},{351,15}});
	//Painter black
	addShapelessRecipe(ItemInstance(Items::ID::mPainterBlack,1,0),
	{{Items::ID::mPainter,-1},{351,0}});
	//Painter pink
	addShapelessRecipe(ItemInstance(Items::ID::mPainterPink,1,0),
	{{Items::ID::mPainter,-1},{351,9}});
	//Painter light green
	addShapelessRecipe(ItemInstance(Items::ID::mPainterGreen,1,0),
	{{Items::ID::mPainter,-1},{351,10}});
	//Painter yellow
	addShapelessRecipe(ItemInstance(Items::ID::mPainterYellow,1,0),
	{{Items::ID::mPainter,-1},{351,11}});
	//Painter orange
	addShapelessRecipe(ItemInstance(Items::ID::mPainterOrange,1,0),
	{{Items::ID::mPainter,-1},{351,14}});
	//Painter gray
	addShapelessRecipe(ItemInstance(Items::ID::mPainterGray,1,0),
	{{Items::ID::mPainter,-1},{351,8}});
	//Painter light gray
	addShapelessRecipe(ItemInstance(Items::ID::mPainterGray,1,0),
	{{Items::ID::mPainter,-1},{351,7}});
	//Painter cyan
	addShapelessRecipe(ItemInstance(Items::ID::mPainterCyan,1,0),
	{{Items::ID::mPainter,-1},{351,6}});
	//Forge hammer
	addShapedRecipe(ItemInstance(Items::ID::mForgeHammer,70,0),{
	"aa ",
	"abb",
	"aa "},{{'a',265,-1},{'b',280,-1}});
	//Cutter
	addShapedRecipe(ItemInstance(Items::ID::mCutter,70,0),{
	"a a",
	" a ",
	"b b"},{{'b',265,-1},{'a',Items::ID::mIronPlate,-1}});
	//Bronze sword
	addShapedRecipe(ItemInstance(Items::ID::mBronzeSword,1,0),{
	"a",
	"a",
	"b",},{{'a',Items::ID::mBronzeIngot,-1},{'b',280,-1}});
	//Bronze pickaxe
	addShapedRecipe(ItemInstance(Items::ID::mBronzePickAxe,1,0),{
	"aaa",
	" b ",
	" b "},{{'a',Items::ID::mBronzeIngot,-1},{'b',280,-1}});
	//Bronze hoe
	addShapedRecipe(ItemInstance(Items::ID::mBronzeHoe,1,0),{
	"aa",
	" b",
	" b"},{{'a',Items::ID::mBronzeIngot,-1},{'b',280,-1}});
	//Bronze shovel
	addShapedRecipe(ItemInstance(Items::ID::mBronzeShovel,1,0),{
	"a",
	"b",
	"b"},{{'a',Items::ID::mBronzeIngot,-1},{'b',280,-1}});
	//Bronze axe
	addShapedRecipe(ItemInstance(Items::ID::mBronzeAxe,1,0),{
	"aa",
	"ab",
	" b"},{{'a',Items::ID::mBronzeIngot,-1},{'b',280,-1}});
	//Circuit
	addShapedRecipe(ItemInstance(Items::ID::mCircuit,1,0),{
	"aaa",
	"bcb",
	"aaa"},{{'a',Items::ID::mCopperCable1,-1},{'b',331,-1},{'c',Items::ID::mIronPlate,-1}});
	//Coil
	addShapedRecipe(ItemInstance(Items::ID::mCoil,2,0),{
	"aaa",
	"aba",
	"aaa"},{{'a',Items::ID::mCopperCable0,-1},{'b',265,-1}});
	//Iron furnace
	addShapedRecipe(ItemInstance(Blocks::ID::mFurnace,1,0),{
	" a ",
	"a a",
	"aba"},{{'a',Items::ID::mIronPlate,-1},{'b',61,-1}});
	//ITNT
	addShapedRecipe(ItemInstance(Blocks::ID::mITNT,4,0),{
	"aaa",
	"bbb",
	"aaa"},{{'a',318,-1},{'b',46,-1}});
	addShapedRecipe(ItemInstance(Blocks::ID::mITNT,4,0),{
	"aba",
	"aba",
	"aba"},{{'a',318,-1},{'b',46,-1}});
	//Planks
	addShapelessRecipe(ItemInstance(5,4,0),
	{{Blocks::ID::mRubberWood,-1}});
	//Tree tap
	addShapedRecipe(ItemInstance(Items::ID::mTreeTap,1,0),{
	" w ",
	"www",
	"w  "},{{'w',5,-1}});
	//Metal blocks
	addShapedRecipe(ItemInstance(Blocks::ID::mMetal,1,0),{
	"aaa",
	"aaa",
	"aaa"},{{'a',Items::ID::mTinIngot,-1}});
	addShapedRecipe(ItemInstance(Blocks::ID::mMetal,1,1),{
	"aaa",
	"aaa",
	"aaa"},{{'a',Items::ID::mSteelIngot,-1}});
	addShapedRecipe(ItemInstance(Blocks::ID::mMetal,1,2),{
	"aaa",
	"aaa",
	"aaa"},{{'a',Items::ID::mCopperIngot,-1}});
	addShapedRecipe(ItemInstance(Blocks::ID::mMetal,1,3),{
	"aaa",
	"aaa",
	"aaa"},{{'a',Items::ID::mLeadIngot,-1}});
	addShapedRecipe(ItemInstance(Blocks::ID::mMetal,1,6),{
	"aaa",
	"aaa",
	"aaa"},{{'a',Items::ID::mBronzeIngot,-1}});
	//Ingots
	addShapelessRecipe(ItemInstance(Items::ID::mTinIngot,9,0),
	{{Blocks::ID::mMetal,0}});
	addShapelessRecipe(ItemInstance(Items::ID::mSteelIngot,9,0),
	{{Blocks::ID::mMetal,1}});
	addShapelessRecipe(ItemInstance(Items::ID::mCopperIngot,9,0),
	{{Blocks::ID::mMetal,2}});
	addShapelessRecipe(ItemInstance(Items::ID::mLeadIngot,9,0),
	{{Blocks::ID::mMetal,3}});
	addShapelessRecipe(ItemInstance(Items::ID::mBronzeIngot,9,0),
	{{Blocks::ID::mMetal,6}});
	//Casing tin
	addShapelessRecipe(ItemInstance(Items::ID::mCasingTin,2,0),
	{{Items::ID::mTinPlate,-1},{Items::ID::mForgeHammer,-1}});
	//Casing copper
	addShapelessRecipe(ItemInstance(Items::ID::mCasingCopper,2,0),
	{{Items::ID::mCopperPlate,-1},{Items::ID::mForgeHammer,-1}});
	//Casing gold
	addShapelessRecipe(ItemInstance(Items::ID::mCasingGold,2,0),
	{{Items::ID::mGoldPlate,-1},{Items::ID::mForgeHammer,-1}});
	//Casing iron
	addShapelessRecipe(ItemInstance(Items::ID::mCasingIron,2,0),
	{{Items::ID::mIronPlate,-1},{Items::ID::mForgeHammer,-1}});
	//Casing bronze
	addShapelessRecipe(ItemInstance(Items::ID::mCasingBronze,2,0),
	{{Items::ID::mBronzePlate,-1},{Items::ID::mForgeHammer,-1}});
	//Casing lead
	addShapelessRecipe(ItemInstance(Items::ID::mCasingLead,2,0),
	{{Items::ID::mLeadPlate,-1},{Items::ID::mForgeHammer,-1}});
	//Casing steel
	addShapelessRecipe(ItemInstance(Items::ID::mCasingSteel,2,0),
	{{Items::ID::mSteelPlate,-1},{Items::ID::mForgeHammer,-1}});
	//Bronze plate
	addShapelessRecipe(ItemInstance(Items::ID::mBronzePlate,1,0),
	{{Items::ID::mBronzeIngot,-1},{Items::ID::mForgeHammer,-1}});
	//Steel plate
	addShapelessRecipe(ItemInstance(Items::ID::mSteelPlate,1,0),
	{{Items::ID::mSteelIngot,-1},{Items::ID::mForgeHammer,-1}});
	//Iron plate
	addShapelessRecipe(ItemInstance(Items::ID::mIronPlate,1,0),
	{{265,-1},{Items::ID::mForgeHammer,-1}});
	//Tin plate
	addShapelessRecipe(ItemInstance(Items::ID::mTinPlate,1,0),
	{{Items::ID::mTinIngot,-1},{Items::ID::mForgeHammer,-1}});
	//Lead plate
	addShapelessRecipe(ItemInstance(Items::ID::mLeadPlate,1,0),
	{{Items::ID::mLeadIngot,-1},{Items::ID::mForgeHammer,-1}});
	//Gold plate
	addShapelessRecipe(ItemInstance(Items::ID::mGoldPlate,1,0),
	{{266,-1},{Items::ID::mForgeHammer,-1}});
	//Copper plate
	addShapelessRecipe(ItemInstance(Items::ID::mCopperPlate,1,0),
	{{Items::ID::mCopperIngot,-1},{Items::ID::mForgeHammer,-1}});
	//Lapis plate
	addShapelessRecipe(ItemInstance(Items::ID::mLapisPlate,1,0),
	{{351,4},{Items::ID::mForgeHammer,-1}});
	//Obsidian plate
	addShapelessRecipe(ItemInstance(Items::ID::mObsidianPlate,1,0),
	{{49,-1},{Items::ID::mForgeHammer,-1}});
	//Uninsulated tin cable
	addShapelessRecipe(ItemInstance(Items::ID::mTinCable0,3,0),
	{{Items::ID::mCutter,-1},{Items::ID::mTinPlate,-1}});
	//Insulated tin cable
	addShapelessRecipe(ItemInstance(Items::ID::mTinCable1,1,0),
	{{Items::ID::mRubber,-1},{Items::ID::mTinCable0,-1}});
	//Uninsulated copper cable
	addShapelessRecipe(ItemInstance(Items::ID::mCopperCable0,2,0),
	{{Items::ID::mCutter,-1},{Items::ID::mCopperPlate,-1}});
	//Insulated copper cable
	addShapelessRecipe(ItemInstance(Items::ID::mCopperCable1,1,0),
	{{Items::ID::mRubber,-1},{Items::ID::mCopperCable0,-1}});
	//Uninsulated gold cable
	addShapelessRecipe(ItemInstance(Items::ID::mGoldCable0,2,0),
	{{Items::ID::mCutter,-1},{Items::ID::mGoldPlate,-1}});
	//Insulated gold cable
	addShapelessRecipe(ItemInstance(Items::ID::mGoldCable1,1,0),
	{{Items::ID::mRubber,-1},{Items::ID::mGoldCable0,-1}});
	//Insulated gold cable
	addShapelessRecipe(ItemInstance(Items::ID::mGoldCable2,1,0),
	{{Items::ID::mRubber,-1},{Items::ID::mRubber,-1},{Items::ID::mGoldCable0,-1}});
	//Insulated gold cable
	addShapelessRecipe(ItemInstance(Items::ID::mGoldCable2,1,0),
	{{Items::ID::mRubber,-1},{Items::ID::mGoldCable1,-1}});
	//Glass cable
	addShapedRecipe(ItemInstance(Items::ID::mGlassCable,1,0),{
	"aaa",
	"bcb",
	"aaa"},{{'a',20,-1},{'b',Items::ID::mEnergiumDust,-1},{'c',Items::ID::mTinDust,-1}});
	//Splitter cable
	//addShapedRecipe(ItemInstance(Items::ID::mSplitterCable,1,0),{
	//" a ",
	//"bcb",
	//" a "},{{'a',331,-1},{'b',Items::ID::mIronCable3,-1},{'c',69,-1}});
	////Detector cable
	//addShapedRecipe(ItemInstance(Items::ID::mDetectorCable,1,0),{
	//" c ",
	//"aba",
	//" a "},{{'a',331,-1},{'b',Items::ID::mIronCable3,-1},{'c',Items::ID::mCircuit,-1}});
	//Insulated iron cable
	addShapelessRecipe(ItemInstance(Items::ID::mIronCable1,1,0),
	{{Items::ID::mRubber,-1},{Items::ID::mIronCable0,-1}});
	//Insulated iron cable
	addShapelessRecipe(ItemInstance(Items::ID::mIronCable2,1,0),
	{{Items::ID::mRubber,-1},{Items::ID::mRubber,-1},{Items::ID::mIronCable0,-1}});
	//Insulated iron cable
	addShapelessRecipe(ItemInstance(Items::ID::mIronCable3,1,0),
	{{Items::ID::mRubber,-1},{Items::ID::mRubber,-1},{Items::ID::mIronCable0,-1}});
	//Insulated iron cable
	addShapelessRecipe(ItemInstance(Items::ID::mIronCable2,1,0),
	{{Items::ID::mRubber,-1},{Items::ID::mIronCable1,-1}});
	//Insulated iron cable
	addShapelessRecipe(ItemInstance(Items::ID::mIronCable3,1,0),
	{{Items::ID::mRubber,-1},{Items::ID::mIronCable2,-1}});
	//Insulated iron cable
	addShapelessRecipe(ItemInstance(Items::ID::mIronCable3,1,0),
	{{Items::ID::mRubber,-1},{Items::ID::mRubber,-1},{Items::ID::mIronCable1,-1}});
	//Single use battery
	addShapedRecipe(ItemInstance(Items::ID::mSingleUseBattery,8,0),{
	"a",
	"b",
	"c"},{{'a',Items::ID::mCopperCable1,-1},{'b',Items::ID::mCoalDust,-1},{'c',331,-1}});
	//Single use battery
	addShapedRecipe(ItemInstance(Items::ID::mSingleUseBattery,8,0),{
	"a",
	"b",
	"c"},{{'a',Items::ID::mCopperCable1,-1},{'b',Items::ID::mCoalFuelDust,-1},{'c',331,-1}});
	//RE battery
	addShapedRecipe(ItemInstance(Items::ID::mReBattery,1,32766),{
	" a ",
	"bcb",
	"bcb"},{{'a',Items::ID::mTinCable1,-1},{'b',Items::ID::mCasingTin,-1},{'c',331,-1}});
	//Machine
	addShapedRecipe(ItemInstance(Blocks::ID::mMetal,1,4),{
	"aaa",
	"a a",
	"aaa"},{{'a',Items::ID::mIronPlate,-1}});
	//Iron
	addShapelessRecipe(ItemInstance(265,8,0),
	{{Blocks::ID::mMetal,4}});
	//Advanced Machine
	addShapedRecipe(ItemInstance(Blocks::ID::mMetal,1,5),{
	"aba",
	"cdc",
	"aba"},{{'a',Items::ID::mSteelPlate,-1},{'b',Items::ID::mAlloyPlate,-1},{'c',Items::ID::mCarbonMesh,-1},{'d',Blocks::ID::mMetal,4}});
	//Electric motor
	addShapedRecipe(ItemInstance(Items::ID::mElectricMotor,1,0),{
	" a ",
	"bcb",
	" a "},{{'a',Items::ID::mCasingTin,-1},{'b',Items::ID::mCoil,-1},{'c',265,-1},{'d',Blocks::ID::mMetal,4}});
	//Advanced circuit
	addShapedRecipe(ItemInstance(Items::ID::mAdvancedCircuit,1,0),{
	"aba",
	"cdc",
	"aba"},{{'a',331,-1},{'b',348,-1},{'c',351,4},{'d',Items::ID::mCircuit,-1}});
	addShapedRecipe(ItemInstance(Items::ID::mAdvancedCircuit,1,0),{
	"aca",
	"bdb",
	"aca"},{{'a',331,-1},{'b',348,-1},{'c',351,4},{'d',Items::ID::mCircuit,-1}});
	//Rubber trampoline
	addShapedRecipe(ItemInstance(Blocks::ID::mResin,3,1),{
	"aaa",
	"aaa"},{{'a',Items::ID::mRubber,-1}});
	//Resin trampoline
	addShapedRecipe(ItemInstance(Blocks::ID::mResin,1,0),{
	"aaa",
	"aaa"},{{'a',Items::ID::mResin,-1}});
	//Power unit
	addShapedRecipe(ItemInstance(Items::ID::mPowerUnit,1,0),{
	"abc",
	"ade",
	"abc"},{{'a',Items::ID::mReBattery,-1},{'b',Items::ID::mCopperCable0,-1},{'d',Items::ID::mCircuit,-1},{'e',Items::ID::mElectricMotor,-1},{'c',Items::ID::mCasingIron,-1}});
	//Small Power unit
	addShapedRecipe(ItemInstance(Items::ID::mPowerUnitSmall,1,0),{
	" bc",
	"ade",
	" bc"},{{'a',Items::ID::mReBattery,-1},{'b',Items::ID::mCopperCable0,-1},{'d',Items::ID::mCircuit,-1},{'e',Items::ID::mElectricMotor,-1},{'c',Items::ID::mCasingIron,-1}});
	//chainsaw
	addShapedRecipe(ItemInstance(Items::ID::mChainsaw,1,32766),{
	" aa",
	"aaa",
	"ba "},{{'a',Items::ID::mIronPlate,-1},{'b',Items::ID::mPowerUnit,-1}});
	//Electric treetap
	addShapelessRecipe(ItemInstance(Items::ID::mElectricTreeTap,1,32766),
	{{Items::ID::mPowerUnitSmall,-1},{Items::ID::mTreeTap,0}});
	//Electric hoe
	addShapedRecipe(ItemInstance(Items::ID::mElectricHoe,1,32766),{
	"aa",
	" a",
	" b"},{{'a',Items::ID::mIronPlate,-1},{'b',Items::ID::mPowerUnitSmall,-1}});
	//Batbox
	addShapedRecipe(ItemInstance(Blocks::ID::mBatBox,1,0),{
	"aba",
	"ccc",
	"aaa"},{{'a',5,-1},{'b',Items::ID::mTinCable1,-1},{'c',Items::ID::mReBattery,-1}});
	//Electric furnace
	addShapedRecipe(ItemInstance(Blocks::ID::mFurnace,1,1),{
	" a ",
	"bcb"},{{'a',Items::ID::mCircuit,0},{'b',331,-1},{'c',Blocks::ID::mFurnace,0}});
	//Electric wrench
	addShapelessRecipe(ItemInstance(Items::ID::mElectricWrench,1,0),
	{{Items::ID::mPowerUnitSmall,-1},{Items::ID::mWrench,0}});
	//Wrench
	addShapedRecipe(ItemInstance(Items::ID::mWrench,1,0),{
	"a a",
	"aaa",
	" a "},{{'a',Items::ID::mBronzeIngot,0}});
	//Bronze armor
	addShapedRecipe(ItemInstance(Items::ID::mChestplate_bronze,1,0),{
	"a a",
	"aaa",
	"aaa"},{{'a',Items::ID::mBronzeIngot,0}});
	addShapedRecipe(ItemInstance(Items::ID::mBoots_bronze,1,0),{
	"a a",
	"a a"},{{'a',Items::ID::mBronzeIngot,0}});
	addShapedRecipe(ItemInstance(Items::ID::mLeggings_bronze,1,0),{
	"aaa"
	"a a",
	"a a"},{{'a',Items::ID::mBronzeIngot,0}});
	addShapedRecipe(ItemInstance(Items::ID::mHelmet_bronze,1,0),{
	"aaa",
	"a a"},{{'a',Items::ID::mBronzeIngot,0}});
	//Bronze dust
	addShapelessRecipe(ItemInstance(Items::ID::mBronzeDust,4,0),
	{{Items::ID::mCopperDust,-1},{Items::ID::mCopperDust,-1},{Items::ID::mCopperDust,-1},{Items::ID::mTinDust,-1}});
	addShapelessRecipe(ItemInstance(Items::ID::mBronzeDust,4,0),
	{{Items::ID::mCrushedCopper,-1},{Items::ID::mPurifiedCopper,-1},{Items::ID::mCopperDust,-1},{Items::ID::mTinDust,-1}});
	addShapelessRecipe(ItemInstance(Items::ID::mBronzeDust,4,0),
	{{Items::ID::mCrushedCopper,-1},{Items::ID::mCrushedCopper,-1},{Items::ID::mCopperDust,-1},{Items::ID::mTinDust,-1}});
	addShapelessRecipe(ItemInstance(Items::ID::mBronzeDust,4,0),
	{{Items::ID::mPurifiedCopper,-1},{Items::ID::mPurifiedCopper,-1},{Items::ID::mCopperDust,-1},{Items::ID::mTinDust,-1}});
	addShapelessRecipe(ItemInstance(Items::ID::mBronzeDust,4,0),
	{{Items::ID::mCrushedCopper,-1},{Items::ID::mCopperDust,-1},{Items::ID::mCopperDust,-1},{Items::ID::mTinDust,-1}});
	addShapelessRecipe(ItemInstance(Items::ID::mBronzeDust,4,0),
	{{Items::ID::mCopperDust,-1},{Items::ID::mPurifiedCopper,-1},{Items::ID::mCopperDust,-1},{Items::ID::mTinDust,-1}});
	addShapelessRecipe(ItemInstance(Items::ID::mBronzeDust,4,0),
	{{Items::ID::mCopperDust,-1},{Items::ID::mCopperDust,-1},{Items::ID::mCopperDust,-1},{Items::ID::mPurifiedTin,-1}});
	addShapelessRecipe(ItemInstance(Items::ID::mBronzeDust,4,0),
	{{Items::ID::mCrushedCopper,-1},{Items::ID::mPurifiedCopper,-1},{Items::ID::mCopperDust,-1},{Items::ID::mPurifiedTin,-1}});
	addShapelessRecipe(ItemInstance(Items::ID::mBronzeDust,4,0),
	{{Items::ID::mCrushedCopper,-1},{Items::ID::mCrushedCopper,-1},{Items::ID::mCopperDust,-1},{Items::ID::mPurifiedTin,-1}});
	addShapelessRecipe(ItemInstance(Items::ID::mBronzeDust,4,0),
	{{Items::ID::mPurifiedCopper,-1},{Items::ID::mPurifiedCopper,-1},{Items::ID::mCopperDust,-1},{Items::ID::mPurifiedTin,-1}});
	addShapelessRecipe(ItemInstance(Items::ID::mBronzeDust,4,0),
	{{Items::ID::mCrushedCopper,-1},{Items::ID::mCopperDust,-1},{Items::ID::mCopperDust,-1},{Items::ID::mPurifiedTin,-1}});
	addShapelessRecipe(ItemInstance(Items::ID::mBronzeDust,4,0),
	{{Items::ID::mCopperDust,-1},{Items::ID::mPurifiedCopper,-1},{Items::ID::mCopperDust,-1},{Items::ID::mPurifiedTin,-1}});
	addShapelessRecipe(ItemInstance(Items::ID::mBronzeDust,4,0),
	{{Items::ID::mCopperDust,-1},{Items::ID::mCopperDust,-1},{Items::ID::mCopperDust,-1},{Items::ID::mCrushedTin,-1}});
	addShapelessRecipe(ItemInstance(Items::ID::mBronzeDust,4,0),
	{{Items::ID::mCrushedCopper,-1},{Items::ID::mPurifiedCopper,-1},{Items::ID::mCopperDust,-1},{Items::ID::mCrushedTin,-1}});
	addShapelessRecipe(ItemInstance(Items::ID::mBronzeDust,4,0),
	{{Items::ID::mCrushedCopper,-1},{Items::ID::mCrushedCopper,-1},{Items::ID::mCopperDust,-1},{Items::ID::mCrushedTin,-1}});
	addShapelessRecipe(ItemInstance(Items::ID::mBronzeDust,4,0),
	{{Items::ID::mPurifiedCopper,-1},{Items::ID::mPurifiedCopper,-1},{Items::ID::mCopperDust,-1},{Items::ID::mCrushedTin,-1}});
	addShapelessRecipe(ItemInstance(Items::ID::mBronzeDust,4,0),
	{{Items::ID::mCrushedCopper,-1},{Items::ID::mCopperDust,-1},{Items::ID::mCopperDust,-1},{Items::ID::mCrushedTin,-1}});
	addShapelessRecipe(ItemInstance(Items::ID::mBronzeDust,4,0),
	{{Items::ID::mCopperDust,-1},{Items::ID::mPurifiedCopper,-1},{Items::ID::mCopperDust,-1},{Items::ID::mCrushedTin,-1}});
	//Macerator
	addShapedRecipe(ItemInstance(Blocks::ID::mMachine1,1,0),{
	"aaa",
	"bcb",
	" d "},{{'a',318,-1},{'b',4,-1},{'c',Blocks::ID::mMetal,4},{'d',Items::ID::mCircuit,-1}});
	//Extractor
	addShapedRecipe(ItemInstance(Blocks::ID::mMachine1,1,1),{
	"aca",
	"ada"},{{'a',Items::ID::mTreeTap,0},{'b',4,-1},{'c',Blocks::ID::mMetal,4},{'d',Items::ID::mCircuit,-1}});
	//Fire generator
	addShapedRecipe(ItemInstance(Blocks::ID::mGenerator1,1,1),{
	" b ",
	"aaa",
	" c "},{{'a',Items::ID::mIronPlate,-1},{'b',Items::ID::mReBattery,-1},{'c',61,-1}});
	addShapedRecipe(ItemInstance(Blocks::ID::mGenerator1,1,1),{
	"b",
	"a",
	"c"},{{'a',Blocks::ID::mMetal,4},{'b',Items::ID::mReBattery,-1},{'c',Blocks::ID::mFurnace,0}});
	//Solar panel
	addShapedRecipe(ItemInstance(Blocks::ID::mGenerator1,1,0),{
	"aba",
	"bab",
	"cdc"},{{'d',Blocks::ID::mMetal,4},{'c',Items::ID::mCircuit,-1},{'b',20,-1},{'a',Items::ID::mCoalDust,-1}});
	addShapedRecipe(ItemInstance(Blocks::ID::mGenerator1,1,0),{
	"bab",
	"aba",
	"cdc"},{{'d',Blocks::ID::mMetal,4},{'c',Items::ID::mCircuit,-1},{'b',20,-1},{'a',Items::ID::mCoalDust,-1}});
	//Luminator
	addShapedRecipe(ItemInstance(Blocks::ID::mLuminator,8,0),{
	"aba",
	"cdc",
	"ccc"},{{'a',Items::ID::mCasingIron,-1},{'b',Items::ID::mCopperCable1,-1},{'d',Items::ID::mTinCable0,-1},{'c',20,-1}});
	//Windmeter
	addShapedRecipe(ItemInstance(Items::ID::mWindMeter,1,32766),{
	" a ",
	"aba",
	" ac"},{{'a',Items::ID::mCasingIron,-1},{'b',Items::ID::mCasingBronze,-1},{'c',Items::ID::mPowerUnitSmall,-1}});
	//Compressor
	addShapedRecipe(ItemInstance(Items::ID::mWindMeter,1,32766),{
	"a a",
	"aba",
	"aca"},{{'a',1,0},{'b',Blocks::ID::mMetal,4},{'c',Items::ID::mCircuit,-1}});
#endif
}
void ICRecipes::addFurnaceRecipes()
{
	using namespace IC;
	
	/*addFurnaceRecipe(Items::ID::mRawCrystalMemory,-1,Items::ID::mCrystalMemory,0);
	addFurnaceRecipe(Items::ID::mResin,-1,Items::ID::mRubber,0);
	addFurnaceRecipe(Blocks::ID::mRubberWood,-1,263,1);
	addFurnaceRecipe(Blocks::ID::mOre,0,Items::ID::mTinIngot,0);
	addFurnaceRecipe(Blocks::ID::mOre,1,Items::ID::mCopperIngot,0);
	addFurnaceRecipe(Blocks::ID::mOre,2,Items::ID::mLeadIngot,0);
	addFurnaceRecipe(Items::ID::mTinDust,-1,Items::ID::mTinIngot,0);
	addFurnaceRecipe(Items::ID::mCopperDust,-1,Items::ID::mCopperIngot,0);
	addFurnaceRecipe(Items::ID::mBronzeDust,-1,Items::ID::mBronzeIngot,0);
	addFurnaceRecipe(Items::ID::mIronDust,-1,265,0);
	addFurnaceRecipe(Items::ID::mGoldDust,-1,266,0);
	addFurnaceRecipe(Items::ID::mLeadDust,-1,Items::ID::mLeadIngot,0);
	addFurnaceRecipe(Items::ID::mLapisDust,-1,351,4);
	addFurnaceRecipe(Items::ID::mCrushedTin,-1,Items::ID::mTinIngot,0);
	addFurnaceRecipe(Items::ID::mCrushedCopper,-1,Items::ID::mCopperIngot,0);
	addFurnaceRecipe(Items::ID::mCrushedIron,-1,265,0);
	addFurnaceRecipe(Items::ID::mCrushedGold,-1,266,0);
	addFurnaceRecipe(Items::ID::mCrushedLead,-1,Items::ID::mLeadIngot,0);
	addFurnaceRecipe(Items::ID::mPurifiedTin,-1,Items::ID::mTinIngot,0);
	addFurnaceRecipe(Items::ID::mPurifiedCopper,-1,Items::ID::mCopperIngot,0);
	addFurnaceRecipe(Items::ID::mPurifiedIron,-1,265,0);
	addFurnaceRecipe(Items::ID::mPurifiedGold,-1,266,0);
	addFurnaceRecipe(Items::ID::mPurifiedLead,-1,Items::ID::mLeadIngot,0);*/
}
void ICRecipes::addExtractorRecipes()
{
	using namespace IC;
	
	/*addExtractorRecipe(Items::ID::mResin,-1,ItemInstance(Items::ID::mRubber,3,0));
	addExtractorRecipe(Blocks::ID::mRubberWood,-1,ItemInstance(Items::ID::mRubber,1,0));
	addExtractorRecipe(Blocks::ID::mRubberSapling,-1,ItemInstance(Items::ID::mRubber,1,0));*/
}
void ICRecipes::addCompressorRecipes()
{
	/*using namespace IC;
	
	addCompressorRecipe(ItemInstance(Items::ID::mBronzePlate,9,0),-1,ItemInstance(Items::ID::mDenseBronzePlate,1,0));
	addCompressorRecipe(ItemInstance(Items::ID::mTinPlate,9,0),-1,ItemInstance(Items::ID::mDenseTinPlate,1,0));
	addCompressorRecipe(ItemInstance(Items::ID::mLeadPlate,9,0),-1,ItemInstance(Items::ID::mDenseLeadPlate,1,0));
	addCompressorRecipe(ItemInstance(Items::ID::mCopperPlate,9,0),-1,ItemInstance(Items::ID::mDenseCopperPlate,1,0));
	addCompressorRecipe(ItemInstance(Items::ID::mIronPlate,9,0),-1,ItemInstance(Items::ID::mDenseIronPlate,1,0));
	addCompressorRecipe(ItemInstance(Items::ID::mGoldPlate,9,0),-1,ItemInstance(Items::ID::mDenseGoldPlate,1,0));
	addCompressorRecipe(ItemInstance(Items::ID::mLapisPlate,9,0),-1,ItemInstance(Items::ID::mDenseLapisPlate,1,0));
	addCompressorRecipe(ItemInstance(Items::ID::mSteelPlate,9,0),-1,ItemInstance(Items::ID::mDenseSteelPlate,1,0));
	addCompressorRecipe(ItemInstance(Items::ID::mObsidianPlate,9,0),-1,ItemInstance(Items::ID::mDenseObsidianPlate,1,0));
	addCompressorRecipe(ItemInstance(332,4,0),-1,ItemInstance(79,1,0));
	addCompressorRecipe(ItemInstance(12,4,0),0,ItemInstance(24,1,0));
	addCompressorRecipe(ItemInstance(12,4,0),1,ItemInstance(179,1,0));
	//addCompressorRecipe(ItemInstance(Items::ID::mPlantBall,1,0),-1,ItemInstance(Items::ID::mDensePlantBall,1,0));
	//addCompressorRecipe(ItemInstance(6,4,0),-1,ItemInstance(Items::ID::mDensePlantBall,1,0));
	//addCompressorRecipe(ItemInstance(18,4,0),-1,ItemInstance(Items::ID::mDensePlantBall,1,0));
	//addCompressorRecipe(ItemInstance(161,4,0),-1,ItemInstance(Items::ID::mDensePlantBall,1,0));
	//addCompressorRecipe(ItemInstance(295,16,0),-1,ItemInstance(Items::ID::mDensePlantBall,1,0));
	//addCompressorRecipe(ItemInstance(361,16,0),-1,ItemInstance(Items::ID::mDensePlantBall,1,0));
	//addCompressorRecipe(ItemInstance(362,16,0),-1,ItemInstance(Items::ID::mDensePlantBall,1,0));
	//addCompressorRecipe(ItemInstance(37,8,0),-1,ItemInstance(Items::ID::mDensePlantBall,1,0));
	//addCompressorRecipe(ItemInstance(38,8,0),-1,ItemInstance(Items::ID::mDensePlantBall,1,0));
	//addCompressorRecipe(ItemInstance(39,8,0),-1,ItemInstance(Items::ID::mDensePlantBall,1,0));
	//addCompressorRecipe(ItemInstance(40,8,0),-1,ItemInstance(Items::ID::mDensePlantBall,1,0));
	//addCompressorRecipe(ItemInstance(391,8,0),-1,ItemInstance(Items::ID::mDensePlantBall,1,0));
	//addCompressorRecipe(ItemInstance(392,4,0),-1,ItemInstance(Items::ID::mDensePlantBall,1,0));
	//addCompressorRecipe(ItemInstance(296,4,0),-1,ItemInstance(Items::ID::mDensePlantBall,1,0));
	//addCompressorRecipe(ItemInstance(338,4,0),-1,ItemInstance(Items::ID::mDensePlantBall,1,0));
	addCompressorRecipe(ItemInstance(Items::ID::mAlloyIngot,1,0),-1,ItemInstance(Items::ID::mAlloyPlate,1,0));
	//addCompressorRecipe(ItemInstance(Items::ID::mSmallPu,9,0),-1,ItemInstance(Items::ID::mPu,1,0));
	//addCompressorRecipe(ItemInstance(Items::ID::mSmallU235,9,0),-1,ItemInstance(Items::ID::mU235,1,0));
	//addCompressorRecipe(ItemInstance(Items::ID::mEmptyCell,1,0),-1,ItemInstance(Items::ID::mAirCompressedCell,1,0));
	//addCompressorRecipe(ItemInstance(Items::ID::mWaterCell,1,0),-1,ItemInstance(80,1,0));
	addCompressorRecipe(ItemInstance(325,1,0),8,ItemInstance(80,1,0));
	//addCompressorRecipe(ItemInstance(Items::ID::mEmergiumDust,9,0),-1,ItemInstance(Items::ID::mEnergyCystal,1,32766));
	addCompressorRecipe(ItemInstance(80,1,0),-1,ItemInstance(79,1,0));
	addCompressorRecipe(ItemInstance(Items::ID::mCarbonMesh,1,0),-1,ItemInstance(Items::ID::mCarbonPlate,1,0));
	//addCompressorRecipe(ItemInstance(Items::ID::mCoalFuelDust,1,0),-1,ItemInstance(Items::ID::mCoalFuel,1,0));
	addCompressorRecipe(ItemInstance(Items::ID::mCoalBlock,1,0),-1,ItemInstance(264,1,0));
	addCompressorRecipe(ItemInstance(Items::ID::mCoalBall,1,0),-1,ItemInstance(Items::ID::mCompressedHydratedCoal,1,0));
	addCompressorRecipe(ItemInstance(348,4,0),-1,ItemInstance(89,1,0));
	addCompressorRecipe(ItemInstance(336,4,0),-1,ItemInstance(45,1,0));
	addCompressorRecipe(ItemInstance(337,4,0),-1,ItemInstance(82,1,0));
	addCompressorRecipe(ItemInstance(Items::ID::mTinDust,1,0),-1,ItemInstance(Items::ID::mTinPlate,1,0));
	addCompressorRecipe(ItemInstance(Items::ID::mCopperDust,1,0),-1,ItemInstance(Items::ID::mCopperPlate,1,0));
	addCompressorRecipe(ItemInstance(Items::ID::mBronzeDust,1,0),-1,ItemInstance(Items::ID::mBronzePlate,1,0));
	addCompressorRecipe(ItemInstance(Items::ID::mIronDust,1,0),-1,ItemInstance(Items::ID::mIronPlate,1,0));
	addCompressorRecipe(ItemInstance(Items::ID::mGoldDust,1,0),-1,ItemInstance(Items::ID::mGoldPlate,1,0));
	addCompressorRecipe(ItemInstance(Items::ID::mLeadDust,1,0),-1,ItemInstance(Items::ID::mLeadPlate,1,0));
	addCompressorRecipe(ItemInstance(Items::ID::mLapisDust,1,0),-1,ItemInstance(Items::ID::mLapisPlate,1,0));*/
}
void ICRecipes::addMaceratorRecipes()
{
	/*using namespace IC;
	
	addMaceratorRecipe(Items::ID::mBioChaff,-1,ItemInstance(3,1,0));
	addMaceratorRecipe(369,-1,ItemInstance(377,5,0));
	addMaceratorRecipe(143,-1,ItemInstance(Items::ID::mCoalDust,9,0));
	addMaceratorRecipe(152,-1,ItemInstance(331,9,0));
	addMaceratorRecipe(155,-1,ItemInstance(406,4,0));
	addMaceratorRecipe(150,-1,ItemInstance(406,4,0));
	addMaceratorRecipe(156,-1,ItemInstance(406,6,0));
	addMaceratorRecipe(352,-1,ItemInstance(351,4,15));
	addMaceratorRecipe(82,-1,ItemInstance(Items::ID::mClayDust,2,0));
	addMaceratorRecipe(263,0,ItemInstance(Items::ID::mCoalDust,1,0));
	addMaceratorRecipe(4,-1,ItemInstance(12,1,0));
	//addMaceratorRecipe(351,3,ItemInstance(Items::ID::mCoffePowder,3,0));
	addMaceratorRecipe(264,-1,ItemInstance(Items::ID::mDiamondDust,1,0));
	//addMaceratorRecipe(Items::ID::mEnergyCrystal,-1,ItemInstance(Items::ID::mEnergiumDust,9,0));
	//addMaceratorRecipe(Items::ID::mFuelRod,-1,ItemInstance(Items::ID::mIronDust,1,0));
	addMaceratorRecipe(89,-1,ItemInstance(348,4,0));
	addMaceratorRecipe(13,-1,ItemInstance(318,4,0));
	addMaceratorRecipe(79,-1,ItemInstance(332,1,0));
	addMaceratorRecipe(Items::ID::mIridiumOre,-1,ItemInstance(Items::ID::mIridiumShard,9,0));
	addMaceratorRecipe(49,-1,ItemInstance(Items::ID::mObsidianDust,9,0));
	//addMaceratorRecipe(394,-1,ItemInstance(Items::ID::mGrinPowder,1,0));
	addMaceratorRecipe(24,-1,ItemInstance(12,1,0));
	//addMaceratorRecipe(375,-1,ItemInstance(Items::ID::mGrinPowder,1,0));
	addMaceratorRecipe(1,-1,ItemInstance(4,1,0));
	//addMaceratorRecipe(Items::ID::mTinCan,-1,ItemInstance(Items::ID::mTinDust,1,0));
	addMaceratorRecipe(35,0,ItemInstance(287,2,0));
	addMaceratorRecipe(31,1,ItemInstance(Items::ID::mBioChaff,1,0));
	addMaceratorRecipe(31,2,ItemInstance(Items::ID::mBioChaff,1,0));
	addMaceratorRecipe(18,-1,ItemInstance(Items::ID::mBioChaff,1,0));
	addMaceratorRecipe(6,-1,ItemInstance(Items::ID::mBioChaff,1,0));
	addMaceratorRecipe(37,-1,ItemInstance(Items::ID::mBioChaff,1,0));
	addMaceratorRecipe(38,-1,ItemInstance(Items::ID::mBioChaff,1,0));
	addMaceratorRecipe(39,-1,ItemInstance(Items::ID::mBioChaff,1,0));
	addMaceratorRecipe(40,-1,ItemInstance(Items::ID::mBioChaff,1,0));
	addMaceratorRecipe(81,-1,ItemInstance(Items::ID::mBioChaff,1,0));
	addMaceratorRecipe(111,-1,ItemInstance(Items::ID::mBioChaff,1,0));
	addMaceratorRecipe(106,-1,ItemInstance(Items::ID::mBioChaff,1,0));
	addMaceratorRecipe(161,-1,ItemInstance(Items::ID::mBioChaff,1,0));
	addMaceratorRecipe(175,-1,ItemInstance(Items::ID::mBioChaff,1,0));
	addMaceratorRecipe(360,-1,ItemInstance(Items::ID::mBioChaff,1,0));
	addMaceratorRecipe(338,-1,ItemInstance(Items::ID::mBioChaff,1,0));
	addMaceratorRecipe(296,-1,ItemInstance(Items::ID::mBioChaff,1,0));
	addMaceratorRecipe(260,-1,ItemInstance(Items::ID::mBioChaff,1,0));
	addMaceratorRecipe(Items::ID::mTinIngot,-1,ItemInstance(Items::ID::mTinDust,1,0));
	addMaceratorRecipe(Items::ID::mCopperIngot,-1,ItemInstance(Items::ID::mCopperDust,1,0));
	addMaceratorRecipe(Items::ID::mBronzeIngot,-1,ItemInstance(Items::ID::mBronzeDust,1,0));
	addMaceratorRecipe(Items::ID::mSteelIngot,-1,ItemInstance(Items::ID::mIronDust,1,0));
	addMaceratorRecipe(Items::ID::mLeadIngot,-1,ItemInstance(Items::ID::mLeadDust,1,0));
	addMaceratorRecipe(265,-1,ItemInstance(Items::ID::mIronDust,1,0));
	addMaceratorRecipe(266,-1,ItemInstance(Items::ID::mGoldDust,1,0));
	addMaceratorRecipe(351,4,ItemInstance(Items::ID::mLapisDust,1,0));
	addMaceratorRecipe(Items::ID::mBronzePlate,-1,ItemInstance(Items::ID::mSmallBronzeDust,8,0));
	addMaceratorRecipe(Items::ID::mGoldPlate,-1,ItemInstance(Items::ID::mSmallGoldDust,8,0));
	addMaceratorRecipe(Items::ID::mIronPlate,-1,ItemInstance(Items::ID::mSmallIronDust,8,0));
	addMaceratorRecipe(Items::ID::mTinPlate,-1,ItemInstance(Items::ID::mSmallTinDust,8,0));
	addMaceratorRecipe(Items::ID::mLeadPlate,-1,ItemInstance(Items::ID::mSmallLeadDust,8,0));
	addMaceratorRecipe(Items::ID::mSteelPlate,-1,ItemInstance(Items::ID::mIronDust,1,0));
	addMaceratorRecipe(Items::ID::mLapisPlate,-1,ItemInstance(Items::ID::mSmallLapisDust,8,0));
	addMaceratorRecipe(Items::ID::mObsidianPlate,-1,ItemInstance(Items::ID::mSmallObsidianDust,8,0));
	addMaceratorRecipe(Items::ID::mCopperPlate,-1,ItemInstance(Items::ID::mSmallCopperDust,8,0));
	addMaceratorRecipe(Items::ID::mDenseBronzePlate,-1,ItemInstance(Items::ID::mBronzeDust,8,0));
	addMaceratorRecipe(Items::ID::mDenseGoldPlate,-1,ItemInstance(Items::ID::mGoldDust,8,0));
	addMaceratorRecipe(Items::ID::mDenseIronPlate,-1,ItemInstance(Items::ID::mIronDust,8,0));
	addMaceratorRecipe(Items::ID::mDenseTinPlate,-1,ItemInstance(Items::ID::mTinDust,8,0));
	addMaceratorRecipe(Items::ID::mDenseLeadPlate,-1,ItemInstance(Items::ID::mLeadDust,8,0));
	addMaceratorRecipe(Items::ID::mDenseSteelPlate,-1,ItemInstance(Items::ID::mIronDust,8,0));
	addMaceratorRecipe(Items::ID::mDenseLapisPlate,-1,ItemInstance(Items::ID::mLapisDust,8,0));
	addMaceratorRecipe(Items::ID::mDenseObsidianPlate,-1,ItemInstance(Items::ID::mObsidianDust,8,0));
	addMaceratorRecipe(Items::ID::mDenseCopperPlate,-1,ItemInstance(Items::ID::mCopperDust,8,0));
	addMaceratorRecipe(Blocks::ID::mOre,3,ItemInstance(Items::ID::mCrushedUranium,2,0));
	addMaceratorRecipe(Blocks::ID::mOre,0,ItemInstance(Items::ID::mCrushedTin,2,0));
	addMaceratorRecipe(Blocks::ID::mOre,1,ItemInstance(Items::ID::mCrushedCopper,2,0));
	addMaceratorRecipe(Blocks::ID::mOre,2,ItemInstance(Items::ID::mCrushedLead,2,0));
	addMaceratorRecipe(15,-1,ItemInstance(Items::ID::mCrushedIron,2,0));
	addMaceratorRecipe(14,-1,ItemInstance(Items::ID::mCrushedGold,2,0));*/
}
void ICRecipes::addShapelessRecipe(ItemInstance const&item,std::vector<ShapelessItemInstance> const&items)
{
	char letter=0;
	ru.clearAllRecipeTypes();
	for(ShapelessItemInstance itemShapeless:items)
		if(itemShapeless.aux==-1)
			ru.addRecipeType(itemShapeless.id,++letter);
		else
			ru.addRecipeTypeAuxValue(itemShapeless.id,itemShapeless.aux,++letter);
	ru.addShapelessRecipe(item);
}
void ICRecipes::addShapedRecipe(ItemInstance const&item,std::vector<std::string>const&map,std::vector<ShapedItemInstance> const&res)
{
	ru.clearAllRecipeTypes();
	for(ShapedItemInstance itemShaped:res)
		if(itemShaped.aux==-1)
			ru.addRecipeType(itemShaped.id,itemShaped.letter);
		else
			ru.addRecipeTypeAuxValue(itemShaped.id,itemShaped.aux,itemShaped.letter);
	ru.addShapedRecipe(item,map);
}
void ICRecipes::addFurnaceRecipe(short id,short aux,short toid,short toaux)
{
	if(aux==-1)
		ru.addFurnaceRecipe(id,toid,toaux);
	else
		ru.addFurnaceRecipe(id,aux,toid,toaux);
}
void ICRecipes::addMaceratorRecipe(unsigned short id,int aux,ItemInstance const&result)
{
	MaceratorRecipes::mInstance->addMaceratorRecipe(id,aux,result);
}
void ICRecipes::addExtractorRecipe(unsigned short id,int aux,ItemInstance const&result)
{
	ExtractorRecipes::mInstance->addExtractorRecipe(id,aux,result);
}
void ICRecipes::addCompressorRecipe(ItemInstance const&from,int aux,ItemInstance const&result)
{
	CompressorRecipes::mInstance->addCompressorRecipe(from,aux,result);
}
