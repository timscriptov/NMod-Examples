#pragma once

#include "mcpe/client/renderer/BlockTessellator.h"

class CableTessellator : public BlockTessellator
{
public:
	bool tessellate(Block const&,BlockPos const&,unsigned char,bool);
private:
	bool isElectricBlockAt(BlockPos const&,BlockPos const&);
};
