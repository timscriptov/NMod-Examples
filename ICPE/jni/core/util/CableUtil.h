#pragma once

#include <string>

#include "mcpe/entity/PaletteColor.h"

class BlockSource;
class BlockPos;

class CableUtil
{
public:
	static bool isTinCable(unsigned char);
	static bool isGlassCable(unsigned char);
	static bool isCopperCable(unsigned char);
	static bool isGoldCable(unsigned char);
	static bool isIronCable(unsigned char);
	static unsigned char dye(unsigned char,unsigned char);
	static int getMaxVoltage(unsigned char);
	static float getResistance(unsigned char);
	static float getSize(unsigned char);
	static int getHurt(int);
	static int getFire(int);
	static bool canDye(unsigned char);
	static bool isHeavyCable(unsigned char);
	static bool isUninsulated(unsigned char);
	static bool canConnectTo(BlockSource&,BlockPos const&,BlockPos const&);
	static bool isDetectorCable(unsigned char);
	static bool isSplitterCable(unsigned char);
};
