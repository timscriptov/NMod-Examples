#include "BlockTextures.h"

#include "mcpe/block/BlockGraphics.h"
#include "mcpe/util/Util.h"

#include "ICPE.h"
#include "Blocks.h"

void BlockTextures::initBlockGraphics()
{
	
	BlockGraphics::mBlocks[IC::Blocks::ID::mRubberSapling]=new BlockGraphics("sapling");
	BlockGraphics::mBlocks[IC::Blocks::ID::mRubberSapling]->setTextureItem("icpe_rubber_sapling");
	BlockGraphics::mBlocks[IC::Blocks::ID::mRubberSapling]->setBlockShape(BlockShape::CROSS);
	BlockGraphics::mBlocks[IC::Blocks::ID::mRubberSapling]->setSoundType(BlockSoundType::GRASS);

	BlockGraphics::mBlocks[IC::Blocks::ID::mRubberWood]=new BlockGraphics("dirt");
	BlockGraphics::mBlocks[IC::Blocks::ID::mRubberWood]->setTextureItem("icpe_rubber_log_top","icpe_rubber_log_top","icpe_rubber_log_side0","icpe_rubber_log_side1","icpe_rubber_log_side2","icpe_rubber_log_side3");
	BlockGraphics::mBlocks[IC::Blocks::ID::mRubberWood]->setSoundType(BlockSoundType::WOOD);
	
	BlockGraphics::mBlocks[IC::Blocks::ID::mResin]=new BlockGraphics("portal");
	BlockGraphics::mBlocks[IC::Blocks::ID::mResin]->setTextureItem("icpe_resin_sheet");
	BlockGraphics::mBlocks[IC::Blocks::ID::mResin]->setSoundType(BlockSoundType::SLIME);
	
	BlockGraphics::mBlocks[IC::Blocks::ID::mRubberLeaves]=new BlockGraphics("portal");
	BlockGraphics::mBlocks[IC::Blocks::ID::mRubberLeaves]->setTextureItem("icpe_rubber_leaves");
	BlockGraphics::mBlocks[IC::Blocks::ID::mRubberLeaves]->setCarriedTextureItem("icpe_rubber_leaves_carried");
	BlockGraphics::mBlocks[IC::Blocks::ID::mRubberLeaves]->setTextureIsotropic(1);
	BlockGraphics::mBlocks[IC::Blocks::ID::mRubberLeaves]->setTextureIsotropic(0);
	BlockGraphics::mBlocks[IC::Blocks::ID::mRubberLeaves]->setSoundType(BlockSoundType::GRASS);
	
	BlockGraphics::mBlocks[IC::Blocks::ID::mCable]=new BlockGraphics("portal");
	BlockGraphics::mBlocks[IC::Blocks::ID::mCable]->setTextureItem("icpe_cable");
	BlockGraphics::mBlocks[IC::Blocks::ID::mCable]->setSoundType(BlockSoundType::STONE);
	
	BlockGraphics::mBlocks[IC::Blocks::ID::mIronFence]=new BlockGraphics("portal");
	BlockGraphics::mBlocks[IC::Blocks::ID::mIronFence]->setTextureItem("icpe_fence_iron");
	BlockGraphics::mBlocks[IC::Blocks::ID::mIronFence]->setBlockShape(BlockShape::FENCE);
	BlockGraphics::mBlocks[IC::Blocks::ID::mIronFence]->setSoundType(BlockSoundType::STONE);
	
	BlockGraphics::mBlocks[IC::Blocks::ID::mResources]=new BlockGraphics("dirt");
	BlockGraphics::mBlocks[IC::Blocks::ID::mResources]->setTextureItem("icpe_res_block_topbottom","icpe_res_block_topbottom","icpe_res_block_sides");
	BlockGraphics::mBlocks[IC::Blocks::ID::mResources]->setSoundType(BlockSoundType::STONE);
	
	/*
	BlockGraphics::mBlocks[IC::Blocks::ID::mFurnace]=new BlockGraphics("dirt");
	BlockGraphics::mBlocks[IC::Blocks::ID::mFurnace]->setTextureItem("icpe_icFurnace_carried_top","icpe_icFurnace_carried_top","icpe_icFurnace_carried_side","icpe_icFurnace_carried_front","icpe_icFurnace_carried_side","icpe_icFurnace_carried_side");
	BlockGraphics::mBlocks[IC::Blocks::ID::mFurnace]->setSoundType(BlockSoundType::STONE);
	
	BlockGraphics::mBlocks[IC::Blocks::ID::mITNT]=new BlockGraphics("tnt");
	BlockGraphics::mBlocks[IC::Blocks::ID::mITNT]->setTextureItem("icpe_itnt_top","icpe_itnt_bottom","icpe_itnt_sides");
	BlockGraphics::mBlocks[IC::Blocks::ID::mITNT]->setTextureIsotropic(1);
	BlockGraphics::mBlocks[IC::Blocks::ID::mITNT]->setTextureIsotropic(0);
	BlockGraphics::mBlocks[IC::Blocks::ID::mITNT]->setSoundType(BlockSoundType::GRASS);
	
	BlockGraphics::mBlocks[IC::Blocks::ID::mGenerator1]=new BlockGraphics("dirt");
	BlockGraphics::mBlocks[IC::Blocks::ID::mGenerator1]->setTextureItem("icpe_generator1_top","icpe_generator1_top","icpe_generator1_side","icpe_generator1_front","icpe_generator1_side","icpe_generator1_side");
	BlockGraphics::mBlocks[IC::Blocks::ID::mGenerator1]->setSoundType(BlockSoundType::STONE);
	
	machine1Default=BlockGraphics::mBlocks[IC::Blocks::ID::mMachine1]=new BlockGraphics("dirt");
	BlockGraphics::mBlocks[IC::Blocks::ID::mMachine1]->setTextureItem("icpe_machine1_top","icpe_machine1_top","icpe_machine1_side","icpe_machine1_front","icpe_machine1_side","icpe_machine1_side");
	BlockGraphics::mBlocks[IC::Blocks::ID::mMachine1]->setSoundType(BlockSoundType::STONE);
	
	batbox1Default=BlockGraphics::mBlocks[IC::Blocks::ID::mBatBox]=new BlockGraphics("dirt");
	BlockGraphics::mBlocks[IC::Blocks::ID::mBatBox]->setTextureItem("icpe_batbox_top","icpe_batbox_top","icpe_batbox_side","icpe_batbox_front","icpe_batbox_side","icpe_batbox_side");
	BlockGraphics::mBlocks[IC::Blocks::ID::mBatBox]->setSoundType(BlockSoundType::STONE);
	*/
	/*BlockGraphics::mBlocks[IC::Blocks::ID::mUUMatterStill]=new BlockGraphics("water");
	BlockGraphics::mBlocks[IC::Blocks::ID::mUUMatterStill]->setTextureItem("icpe_uu_matter_still");
	BlockGraphics::mBlocks[IC::Blocks::ID::mUUMatterStill]->setBlockShape(BlockShape::LIQUID);
	
	BlockGraphics::mBlocks[IC::Blocks::ID::mUUMatterFlow]=new BlockGraphics("flowing_water");
	BlockGraphics::mBlocks[IC::Blocks::ID::mUUMatterFlow]->setTextureItem("icpe_uu_matter_flow");
	BlockGraphics::mBlocks[IC::Blocks::ID::mUUMatterFlow]->setBlockShape(BlockShape::LIQUID);
	
	/*BlockGraphics::mBlocks[IC::Blocks::ID::mLuminator]=new BlockGraphics("portal");
	BlockGraphics::mBlocks[IC::Blocks::ID::mLuminator]->setTextureItem("icpe_luminator");
	BlockGraphics::mBlocks[IC::Blocks::ID::mLuminator]->setSoundType(BlockSoundType::GLASS);
	
	BlockGraphics::mBlocks[IC::Blocks::ID::mLuminatorActive]=new BlockGraphics("portal");
	BlockGraphics::mBlocks[IC::Blocks::ID::mLuminatorActive]->setTextureItem("icpe_luminator_active");
	BlockGraphics::mBlocks[IC::Blocks::ID::mLuminatorActive]->setSoundType(BlockSoundType::GLASS);
	
	ironFurnaceUnLit[0]->setTextureItem("icpe_ironFurnace_top","icpe_ironFurnace_bottom","icpe_ironFurnace_unlit","icpe_ironFurnace_side","icpe_ironFurnace_side","icpe_ironFurnace_side");
	ironFurnaceUnLit[1]->setTextureItem("icpe_ironFurnace_top","icpe_ironFurnace_bottom","icpe_ironFurnace_side","icpe_ironFurnace_unlit","icpe_ironFurnace_side","icpe_ironFurnace_side");
	ironFurnaceUnLit[2]->setTextureItem("icpe_ironFurnace_top","icpe_ironFurnace_bottom","icpe_ironFurnace_side","icpe_ironFurnace_side","icpe_ironFurnace_unlit","icpe_ironFurnace_side");
	ironFurnaceUnLit[3]->setTextureItem("icpe_ironFurnace_top","icpe_ironFurnace_bottom","icpe_ironFurnace_side","icpe_ironFurnace_side","icpe_ironFurnace_side","icpe_ironFurnace_unlit");
	ironFurnaceLit[0]->setTextureItem("icpe_ironFurnace_top","icpe_ironFurnace_bottom","icpe_ironFurnace_lit","icpe_ironFurnace_side","icpe_ironFurnace_side","icpe_ironFurnace_side");
	ironFurnaceLit[1]->setTextureItem("icpe_ironFurnace_top","icpe_ironFurnace_bottom","icpe_ironFurnace_side","icpe_ironFurnace_lit","icpe_ironFurnace_side","icpe_ironFurnace_side");
	ironFurnaceLit[2]->setTextureItem("icpe_ironFurnace_top","icpe_ironFurnace_bottom","icpe_ironFurnace_side","icpe_ironFurnace_side","icpe_ironFurnace_lit","icpe_ironFurnace_side");
	ironFurnaceLit[3]->setTextureItem("icpe_ironFurnace_top","icpe_ironFurnace_bottom","icpe_ironFurnace_side","icpe_ironFurnace_side","icpe_ironFurnace_side","icpe_ironFurnace_lit");
	fireGeneratorUnLit[0]->setTextureItem("icpe_fireGenerator_top","icpe_fireGenerator_bottom","icpe_fireGenerator_unlit","icpe_fireGenerator_side","icpe_fireGenerator_side","icpe_fireGenerator_side");
	fireGeneratorUnLit[1]->setTextureItem("icpe_fireGenerator_top","icpe_fireGenerator_bottom","icpe_fireGenerator_side","icpe_fireGenerator_unlit","icpe_fireGenerator_side","icpe_fireGenerator_side");
	fireGeneratorUnLit[2]->setTextureItem("icpe_fireGenerator_top","icpe_fireGenerator_bottom","icpe_fireGenerator_side","icpe_fireGenerator_side","icpe_fireGenerator_unlit","icpe_fireGenerator_side");
	fireGeneratorUnLit[3]->setTextureItem("icpe_fireGenerator_top","icpe_fireGenerator_bottom","icpe_fireGenerator_side","icpe_fireGenerator_side","icpe_fireGenerator_side","icpe_fireGenerator_unlit");
	fireGeneratorLit[0]->setTextureItem("icpe_fireGenerator_top","icpe_fireGenerator_bottom","icpe_fireGenerator_lit","icpe_fireGenerator_side","icpe_fireGenerator_side","icpe_fireGenerator_side");
	fireGeneratorLit[1]->setTextureItem("icpe_fireGenerator_top","icpe_fireGenerator_bottom","icpe_fireGenerator_side","icpe_fireGenerator_lit","icpe_fireGenerator_side","icpe_fireGenerator_side");
	fireGeneratorLit[2]->setTextureItem("icpe_fireGenerator_top","icpe_fireGenerator_bottom","icpe_fireGenerator_side","icpe_fireGenerator_side","icpe_fireGenerator_lit","icpe_fireGenerator_side");
	fireGeneratorLit[3]->setTextureItem("icpe_fireGenerator_top","icpe_fireGenerator_bottom","icpe_fireGenerator_side","icpe_fireGenerator_side","icpe_fireGenerator_side","icpe_fireGenerator_lit");
	electricFurnaceUnLit[0]->setTextureItem("icpe_electricFurnace_top","icpe_electricFurnace_bottom","icpe_electricFurnace_unlit","icpe_electricFurnace_side","icpe_electricFurnace_side","icpe_electricFurnace_side");
	electricFurnaceUnLit[1]->setTextureItem("icpe_electricFurnace_top","icpe_electricFurnace_bottom","icpe_electricFurnace_side","icpe_electricFurnace_unlit","icpe_electricFurnace_side","icpe_electricFurnace_side");
	electricFurnaceUnLit[2]->setTextureItem("icpe_electricFurnace_top","icpe_electricFurnace_bottom","icpe_electricFurnace_side","icpe_electricFurnace_side","icpe_electricFurnace_unlit","icpe_electricFurnace_side");
	electricFurnaceUnLit[3]->setTextureItem("icpe_electricFurnace_top","icpe_electricFurnace_bottom","icpe_electricFurnace_side","icpe_electricFurnace_side","icpe_electricFurnace_side","icpe_electricFurnace_unlit");
	electricFurnaceLit[0]->setTextureItem("icpe_electricFurnace_top","icpe_electricFurnace_bottom","icpe_electricFurnace_lit","icpe_electricFurnace_side","icpe_electricFurnace_side","icpe_electricFurnace_side");
	electricFurnaceLit[1]->setTextureItem("icpe_electricFurnace_top","icpe_electricFurnace_bottom","icpe_electricFurnace_side","icpe_electricFurnace_lit","icpe_electricFurnace_side","icpe_electricFurnace_side");
	electricFurnaceLit[2]->setTextureItem("icpe_electricFurnace_top","icpe_electricFurnace_bottom","icpe_electricFurnace_side","icpe_electricFurnace_side","icpe_electricFurnace_lit","icpe_electricFurnace_side");
	electricFurnaceLit[3]->setTextureItem("icpe_electricFurnace_top","icpe_electricFurnace_bottom","icpe_electricFurnace_side","icpe_electricFurnace_side","icpe_electricFurnace_side","icpe_electricFurnace_lit");
	rubberWood[0]->setTextureItem("icpe_rubberwood_top","icpe_rubberwood_op","icpe_rubberwood_side","icpe_rubberwood_side","icpe_rubberwood_side","icpe_rubberwood_side");
	rubberWood[1]->setTextureItem("icpe_rubberwood_side","icpe_rubberwood_e","icpe_rubberwood_top","icpe_rubberwood_top","icpe_rubberwood_sidefallen","icpe_rubberwood_sidefallen");
	rubberWood[2]->setTextureItem("icpe_rubberwood_side","icpe_rubberwood_d","icpe_rubberwood_side","icpe_rubberwood_sidefallen","icpe_rubberwood_top","icpe_rubberwood_top");
	rubberWood[3]->setTextureItem("icpe_rubberwood_top","icpe_rubberwood_top","icpe_rubberwood_dry","icpe_rubberwood_side","icpe_rubberwood_side","icpe_rubberwood_side");
	rubberWood[4]->setTextureItem("icpe_rubberwood_top","icpe_rubberwood_top","icpe_rubberwood_side","icpe_rubberwood_dry","icpe_rubberwood_side","icpe_rubberwood_side");
	rubberWood[5]->setTextureItem("icpe_rubberwood_top","icpe_rubberwood_top","icpe_rubberwood_side","icpe_rubberwood_side","icpe_rubberwood_dry","icpe_rubberwood_side");
	rubberWood[6]->setTextureItem("icpe_rubberwood_top","icpe_rubberwood_top","icpe_rubberwood_side","icpe_rubberwood_side","icpe_rubberwood_side","icpe_rubberwood_side");
	rubberWood[7]->setTextureItem("icpe_rubberwood_top","icpe_rubberwood_top","icpe_rubberwood_wet","icpe_rubberwood_side","icpe_rubberwood_side","icpe_rubberwood_side");
	rubberWood[8]->setTextureItem("icpe_rubberwood_top","icpe_rubberwood_top","icpe_rubberwood_side","icpe_rubberwood_wet","icpe_rubberwood_side","icpe_rubberwood_side");
	rubberWood[9]->setTextureItem("icpe_rubberwood_top","icpe_rubberwood_top","icpe_rubberwood_side","icpe_rubberwood_side","icpe_rubberwood_wet","icpe_rubberwood_side");
	rubberWood[10]->setTextureItem("icpe_rubberwood_top","icpe_rubberwood_top","icpe_rubberwood_side","icpe_rubberwood_side","icpe_rubberwood_side","icpe_rubberwood_wet");
	batbox[0]->setTextureItem("icpe_batbox_top","icpe_batbox_front","icpe_batbox_side","icpe_batbox_side","icpe_batbox_side","icpe_batbox_side");
	batbox[1]->setTextureItem("icpe_batbox_front","icpe_batbox_top","icpe_batbox_side","icpe_batbox_side","icpe_batbox_side","icpe_batbox_side");
	batbox[2]->setTextureItem("icpe_batbox_top","icpe_batbox_bottom","icpe_batbox_back","icpe_batbox_front","icpe_batbox_side","icpe_batbox_side");
	batbox[3]->setTextureItem("icpe_batbox_top","icpe_batbox_bottom","icpe_batbox_front","icpe_batbox_back","icpe_batbox_side","icpe_batbox_side");
	batbox[4]->setTextureItem("icpe_batbox_top","icpe_batbox_bottom","icpe_batbox_side","icpe_batbox_side","icpe_batbox_back","icpe_batbox_front");
	batbox[5]->setTextureItem("icpe_batbox_top","icpe_batbox_bottom","icpe_batbox_side","icpe_batbox_side","icpe_batbox_front","icpe_batbox_back");
	solarGenerator->setTextureItem("icpe_solar_generator_top","icpe_solar_generator_bottom","icpe_solar_generator_sides","icpe_solar_generator_sides","icpe_solar_generator_sides","icpe_solar_generator_sides");
	maceratorUnLit[0]->setTextureItem("icpe_macerator_top","icpe_macerator_bottom","icpe_macerator_unlit","icpe_macerator_side","icpe_macerator_side","icpe_macerator_side");
	maceratorUnLit[1]->setTextureItem("icpe_macerator_top","icpe_macerator_bottom","icpe_macerator_side","icpe_macerator_unlit","icpe_macerator_side","icpe_macerator_side");
	maceratorUnLit[2]->setTextureItem("icpe_macerator_top","icpe_macerator_bottom","icpe_macerator_side","icpe_macerator_side","icpe_macerator_unlit","icpe_macerator_side");
	maceratorUnLit[3]->setTextureItem("icpe_macerator_top","icpe_macerator_bottom","icpe_macerator_side","icpe_macerator_side","icpe_macerator_side","icpe_macerator_unlit");
	maceratorLit[0]->setTextureItem("icpe_macerator_top_lit","icpe_macerator_bottom","icpe_macerator_lit","icpe_macerator_side","icpe_macerator_side","icpe_macerator_side");
	maceratorLit[1]->setTextureItem("icpe_macerator_top_lit","icpe_macerator_bottom","icpe_macerator_side","icpe_macerator_lit","icpe_macerator_side","icpe_macerator_side");
	maceratorLit[2]->setTextureItem("icpe_macerator_top_lit","icpe_macerator_bottom","icpe_macerator_side","icpe_macerator_side","icpe_macerator_lit","icpe_macerator_side");
	maceratorLit[3]->setTextureItem("icpe_macerator_top_lit","icpe_macerator_bottom","icpe_macerator_side","icpe_macerator_side","icpe_macerator_side","icpe_macerator_lit");
	extractorUnLit[0]->setTextureItem("icpe_extractor_top","icpe_extractor_bottom","icpe_extractor_unlit","icpe_extractor_back","icpe_extractor_side_unlit","icpe_extractor_side_unlit");
	extractorUnLit[1]->setTextureItem("icpe_extractor_top","icpe_extractor_bottom","icpe_extractor_back","icpe_extractor_unlit","icpe_extractor_side_unlit","icpe_extractor_side_unlit");
	extractorUnLit[2]->setTextureItem("icpe_extractor_top","icpe_extractor_bottom","icpe_extractor_side_unlit","icpe_extractor_side_unlit","icpe_extractor_unlit","icpe_extractor_back");
	extractorUnLit[3]->setTextureItem("icpe_extractor_top","icpe_extractor_bottom","icpe_extractor_side_unlit","icpe_extractor_side_unlit","icpe_extractor_back","icpe_extractor_unlit");
	extractorLit[0]->setTextureItem("icpe_extractor_top","icpe_extractor_bottom","icpe_extractor_lit","icpe_extractor_back","icpe_extractor_side_lit","icpe_extractor_side_lit");
	extractorLit[1]->setTextureItem("icpe_extractor_top","icpe_extractor_bottom","icpe_extractor_back","icpe_extractor_lit","icpe_extractor_side_lit","icpe_extractor_side_lit");
	extractorLit[2]->setTextureItem("icpe_extractor_top","icpe_extractor_bottom","icpe_extractor_side_lit","icpe_extractor_side_lit","icpe_extractor_lit","icpe_extractor_back");
	extractorLit[3]->setTextureItem("icpe_extractor_top","icpe_extractor_bottom","icpe_extractor_side_lit","icpe_extractor_side_lit","icpe_extractor_back","icpe_extractor_lit");
	compressorUnLit[0]->setTextureItem("icpe_compressor_top","icpe_compressor_bottom","icpe_compressor_unlit","icpe_compressor_side","icpe_compressor_side","icpe_compressor_side");
	compressorUnLit[1]->setTextureItem("icpe_compressor_top","icpe_compressor_bottom","icpe_compressor_side","icpe_compressor_unlit","icpe_compressor_side","icpe_compressor_side");
	compressorUnLit[2]->setTextureItem("icpe_compressor_top","icpe_compressor_bottom","icpe_compressor_side","icpe_compressor_side","icpe_compressor_unlit","icpe_compressor_side");
	compressorUnLit[3]->setTextureItem("icpe_compressor_top","icpe_compressor_bottom","icpe_compressor_side","icpe_compressor_side","icpe_compressor_side","icpe_compressor_unlit");
	compressorLit[0]->setTextureItem("icpe_compressor_top","icpe_compressor_bottom","icpe_compressor_lit","icpe_compressor_side","icpe_compressor_side","icpe_compressor_side");
	compressorLit[1]->setTextureItem("icpe_compressor_top","icpe_compressor_bottom","icpe_compressor_side","icpe_compressor_lit","icpe_compressor_side","icpe_compressor_side");
	compressorLit[2]->setTextureItem("icpe_compressor_top","icpe_compressor_bottom","icpe_compressor_side","icpe_compressor_side","icpe_compressor_lit","icpe_compressor_side");
	compressorLit[3]->setTextureItem("icpe_compressor_top","icpe_compressor_bottom","icpe_compressor_side","icpe_compressor_side","icpe_compressor_side","icpe_compressor_lit");*/
}
void BlockTextures::teardownBlockGraphics()
{
	
}
