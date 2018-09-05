#pragma once

class ItemInstance;

#include "items/PainterAux.h"

class ItemUtils
{
public:
	static unsigned long getMaxEnergy(ItemInstance const&);
	static bool isICItem(ItemInstance const&);
	static unsigned long getEnergy(ItemInstance const&);
	static unsigned int getIVoltage(ItemInstance const&);
	static unsigned int getOVoltage(ItemInstance const&);
	static bool isEnergyStorageItem(ItemInstance const&);
	static void setEnergy(ItemInstance&,unsigned long);
	static bool canCharge(ItemInstance const&);
	static void setPainterType(ItemInstance&,PainterAux);
	static PainterAux getPainterType(ItemInstance const&);
};
