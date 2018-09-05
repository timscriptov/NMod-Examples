#include "CableUtil.h"

#include "mcpe/level/BlockSource.h"
#include "mcpe/util/FullBlock.h"

#include "items/Items.h"
#include "blocks/Blocks.h"

#include "blocks/blockentity/CableBlockEntity.h"

bool CableUtil::isTinCable(unsigned char aux)
{
	return aux==0||aux==1;
}
bool CableUtil::isGlassCable(unsigned char aux)
{
	return aux==11;
}
bool CableUtil::isCopperCable(unsigned char aux)
{
	return aux==2||aux==3;
}
bool CableUtil::isGoldCable(unsigned char aux)
{
	return aux==4||aux==5||aux==6;
}
bool CableUtil::isIronCable(unsigned char aux)
{
	return aux==7||aux==8||aux==9||aux==10;
}
bool CableUtil::isDetectorCable(unsigned char aux)
{
	return aux==12||aux==13;
}
bool CableUtil::isSplitterCable(unsigned char aux)
{
	return aux==14||aux==15;
}
bool CableUtil::isHeavyCable(unsigned char aux)
{
	return aux==10;
}
float CableUtil::getSize(unsigned char aux)
{
	switch(aux)
	{
	case 0:case 2:case 4:case 11:
		return 0.375;
	case 10:
		return 0.1875;
	case 9:case 8:
		return 0.25;
	case 7:case 6:case 5:case 3:case 1:case 12:case 13:case 14:case 15:
		return 0.3125;
	}
	return 0;
}
bool CableUtil::canDye(unsigned char aux)
{
	return aux==1||aux==3||aux==5||aux==6||aux==8||aux==9||aux==10||aux==11;
}
unsigned char CableUtil::dye(unsigned char aux,unsigned char colorType)
{
	if(canDye(aux))
		return aux + colorType * 16;
	return aux;
}
int CableUtil::getMaxVoltage(unsigned char aux)
{
	if(isTinCable(aux))
		return 32;
	else if(isCopperCable(aux))
		return 128;
	else if(isIronCable(aux))
		return 2048;
	else if(isGoldCable(aux))
		return 512;
	return 78192;
}
float CableUtil::getResistance(unsigned char aux)
{
	if(isUninsulated(aux))
	{
		if(isTinCable(aux))
			return 0.025;
		else if(isCopperCable(aux))
			return 0.3;
		else if(isIronCable(aux))
			return 1.0;
		else if(isGoldCable(aux))
			return 0.5;
		return 0;
	}
	if(isTinCable(aux))
		return 0.02;
	else if(isCopperCable(aux))
		return 0.2;
	else if(isIronCable(aux))
	{
		if(aux==8)
			return 0.95;
		else if(aux==9)
			return 0.9;
		return 0.8;
	}
	else if(isGoldCable(aux))
	{
		if(aux==5)
			return 0.45;
		return 0.4;
	}
	return 0.025;
}
int CableUtil::getHurt(int voltage)
{
	return voltage>32;
}
int CableUtil::getFire(int voltage)
{
	return (voltage-32)/10;
}
bool CableUtil::isUninsulated(unsigned char aux)
{
	return aux==0||aux==2||aux==4||aux==7;
}
bool CableUtil::canConnectTo(BlockSource&s,BlockPos const&pos1,BlockPos const&pos2)
{
	bool isCable1=s.getBlock(pos1)==Block::mBlocks[IC::Blocks::ID::mCable];
	bool isCable2=s.getBlock(pos2)==Block::mBlocks[IC::Blocks::ID::mCable];
	
	if(isCable1&&isCable2)
	{
		CableBlockEntity* cableEnt1=(CableBlockEntity*)s.getBlockEntity(pos1);
		CableBlockEntity* cableEnt2=(CableBlockEntity*)s.getBlockEntity(pos2);
		
		if(cableEnt1&&cableEnt2&&cableEnt1->getColor()==cableEnt2->getColor())
			return true;
		else if(cableEnt1&&cableEnt2)
			return false;
	}
	if(isCable1&&!isCable2)
	{
		return IC::Blocks::mICBlocks[s.getBlock(pos2)->blockId]&&((IC::Blocks*)s.getBlock(pos2))->isElectricBlock(s,pos2);
	}
	if(!isCable1&&isCable2)
	{
		return IC::Blocks::mICBlocks[s.getBlock(pos1)->blockId]&&((IC::Blocks*)s.getBlock(pos1))->isElectricBlock(s,pos1);
	}
	if(!isCable1&&!isCable2)
	{
		return IC::Blocks::mICBlocks[s.getBlock(pos1)->blockId]&&((IC::Blocks*)s.getBlock(pos1))->isElectricBlock(s,pos1)&&IC::Blocks::mICBlocks[s.getBlock(pos2)->blockId]&&((IC::Blocks*)s.getBlock(pos2))->isElectricBlock(s,pos2);
	}
	return false;
}
