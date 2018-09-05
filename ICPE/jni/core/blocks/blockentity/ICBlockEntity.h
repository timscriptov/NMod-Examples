#pragma once

#include <string>

#include "util/FacingEnum.h"
#include "blocks/cblockentity/CBlockEntity.h"

class ICBlockEntity : public CBlockEntity
{
public:
	ICBlockEntity(BlockPos const&);
	~ICBlockEntity()=default;
public:
	virtual bool isMachine()const;
	virtual bool isElectricMachine()const;
	virtual bool isEnergyProvider(FacingEnum)const;
	virtual bool isEnergyReceiver(FacingEnum)const;
	virtual bool isEnergyConductor()const;
protected:
	void updateTessellator(BlockSource&);
};
