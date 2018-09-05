#pragma once

#include <memory>

class BlockSource;
class BlockPos;
class Biome;
class Random;
class Feature;
class BiomeDecorator;

namespace IC
{
class FeatureGen
{
private:
	static bool inited;
	static std::unique_ptr<Feature> rubTree;
	static std::unique_ptr<Feature> fallenRubTree;
	static std::unique_ptr<Feature> tinOre;
	static std::unique_ptr<Feature> copperOre;
	static std::unique_ptr<Feature> leadOre;
	static std::unique_ptr<Feature> uraniumOre;
public:
	static void decorateChunk(BiomeDecorator*,BlockSource&, Random&,Biome*,BlockPos const&);
private:
	static unsigned int getRubGenChance(Biome&);
	static void prepare();
};
}
