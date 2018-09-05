#include "ICBlockEntity.h"

#include <stdio.h>

#include "mcpe/util/Util.h"
#include "mcpe/client/MinecraftGame.h"
#include "mcpe/client/renderer/LevelRenderer.h"
#include "mcpe/util/DimensionId.h"
#include "mcpe/level/BlockSource.h"

#include "ICPE.h"

ICBlockEntity::ICBlockEntity(BlockPos const&pos):CBlockEntity(pos)
{
	
}
bool ICBlockEntity::isMachine()const
{
	return false;
}
bool ICBlockEntity::isEnergyProvider(FacingEnum)const
{
	return false;
}
bool ICBlockEntity::isEnergyConductor()const
{
	return false;
}
bool ICBlockEntity::isEnergyReceiver(FacingEnum)const
{
	return false;
}
bool ICBlockEntity::isElectricMachine()const
{
	return false;
}
void ICBlockEntity::updateTessellator(BlockSource&s)
{
	BlockPos startPos(getPosition().x-8,getPosition().y-8,getPosition().z-8);
	BlockPos endPos(getPosition().x+8,getPosition().y+8,getPosition().z+8);
	
	ICPE::pMinecraftGame->getLevelRenderer()->onAreaChanged(s,startPos,endPos);
}
