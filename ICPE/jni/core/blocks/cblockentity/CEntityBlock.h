#pragma once

#include "mcpe/block/blocks/EntityBlock.h"

class CBlockEntity;

class CEntityBlock : public EntityBlock
{
public:
	CEntityBlock(std::string const&,short,Material const&);
public:
	virtual std::unique_ptr<CBlockEntity> createBlockEntity(BlockPos const&)const=0;
};
