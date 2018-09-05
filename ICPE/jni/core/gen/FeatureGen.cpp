#include "FeatureGen.h"

#include <stdlib.h>

#include "blocks/Blocks.h"

#include "feature/RubTreeFeature.h"
#include "feature/FallenRubTreeFeature.h"

#include "mcpe/level/gen/Feature.h"
#include "mcpe/level/gen/OreFeature.h"
#include "mcpe/level/biome/Biome.h"
#include "mcpe/level/biome/BiomeDecorator.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/level/Level.h"
#include "mcpe/util/Random.h"
#include "mcpe/util/ChunkPos.h"

namespace IC
{

bool FeatureGen::inited=false;
std::unique_ptr<Feature> FeatureGen::rubTree;
std::unique_ptr<Feature> FeatureGen::fallenRubTree;
std::unique_ptr<Feature> FeatureGen::tinOre;
std::unique_ptr<Feature> FeatureGen::copperOre;
std::unique_ptr<Feature> FeatureGen::uraniumOre;
std::unique_ptr<Feature> FeatureGen::leadOre;

void FeatureGen::decorateChunk(BiomeDecorator*bd,BlockSource&s, Random&random,Biome*biome,BlockPos const&pos)
{
	prepare();
	
	//rubber trees
	for(int x=pos.x;x<pos.x+16;++x)
		for(int z=pos.z;z<pos.z+16;++z)
			for(int y=256;y>50;--y)
				if(s.getBlock(x,y,z)==Block::mGrass&&getRubGenChance(*biome)!=0&&random.nextBool(getRubGenChance(*biome)))
					bd->_placeFeature(&s,rubTree,BlockPos(x,y+1,z),random);
	
	for(int x=pos.x;x<pos.x+16;++x)
		for(int z=pos.z;z<pos.z+16;++z)
			for(int y=256;y>50;--y)
				if(s.getBlock(x,y,z)==Block::mGrass&&(getRubGenChance(*biome)*2)!=0&&random.nextBool(getRubGenChance(*biome)*2))
					bd->_placeFeature(&s,fallenRubTree,BlockPos(x,y+1,z),random);
	
	
	//uranium ore
	for(int x=pos.x;x<pos.x+16;++x)
		for(int y=0;y<65;++y)
			for(int z=pos.z;z<pos.z+16;++z)
				if(random.nextBool(4000))
					bd->_placeFeature(&s,uraniumOre,BlockPos(x,y,z),random);
	//copper ore
	for(int x=pos.x;x<pos.x+16;++x)
		for(int y=10;y<70;++y)
			for(int z=pos.z;z<pos.z+16;++z)
				if(random.nextBool(1000))
					bd->_placeFeature(&s,copperOre,BlockPos(x,y,z),random);
	//tin ore
	for(int x=pos.x;x<pos.x+16;++x)
		for(int y=0;y<40;++y)
			for(int z=pos.z;z<pos.z+16;++z)
				if(random.nextBool(1000))
					bd->_placeFeature(&s,tinOre,BlockPos(x,y,z),random);
	//lead ore
	for(int x=pos.x;x<pos.x+16;++x)
		for(int y=0;y<65;++y)
			for(int z=pos.z;z<pos.z+16;++z)
				if(random.nextBool(2000))
					bd->_placeFeature(&s,leadOre,BlockPos(x,y,z),random);
}
unsigned int FeatureGen::getRubGenChance(Biome&b)
{
	if(&b==Biome::forest||&b==Biome::extremeHillsWithTrees||&b==Biome::extremeHillsWithTreesMutated||&b==Biome::forestHills||&b==Biome::forestMutated||&b==Biome::plainsMutated)
		return 8500;
	if(&b==Biome::taiga||&b==Biome::taigaHills)
		return 7225;
	if(&b==Biome::swampland||&b==Biome::swamplandMutated)
		return 5950;
	if(&b==Biome::taigaMutated)
		return 85;
	return 0;
}
void FeatureGen::prepare()
{
	if(inited)
		return;
	inited=true;
	
	
	tinOre=std::unique_ptr<OreFeature>(new OreFeature(Blocks::ID::mResources,8,8));
	copperOre=std::unique_ptr<OreFeature>(new OreFeature(Blocks::ID::mResources,9,10));
	leadOre=std::unique_ptr<OreFeature>(new OreFeature(Blocks::ID::mResources,10,5));
	uraniumOre=std::unique_ptr<OreFeature>(new OreFeature(Blocks::ID::mResources,11,2));
	fallenRubTree=std::unique_ptr<FallenRubTreeFeature>(new FallenRubTreeFeature(FullBlock(Blocks::ID::mRubberWood,0)));
	rubTree=std::unique_ptr<RubTreeFeature>(new RubTreeFeature(FullBlock(Blocks::ID::mRubberWood,0),FullBlock(Blocks::ID::mRubberWood,2),FullBlock(Blocks::ID::mRubberLeaves,0),15));
}
}
