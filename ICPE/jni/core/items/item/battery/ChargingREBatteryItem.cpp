#include "ChargingREBatteryItem.h"

#include <math.h>

ChargingREBatteryItem::ChargingREBatteryItem():EnergyStorageItem("charging_re_battery",ID::mChargingReBattery-0x100)
{
	setCategory(CreativeItemCategory::TOOLS);
	setMaxStackSize(1);
	setStackedByData(true);
}
unsigned long ChargingREBatteryItem::getMaxEnergy()const
{
	return 4E4;
}
TextureUVCoordinateSet const& ChargingREBatteryItem::getIcon(int aux, int i, bool b) const
{
	aux=32766-aux;
	int auxTex=0;
	if(aux>=0&&aux<6554)
		auxTex=0;
	else if(aux>=6554&&aux<13106)
		auxTex=1;
	else if(aux>=13106&&aux<19660)
		auxTex=2;
	else if(aux>=19660&&aux<26213)
		auxTex=3;
	else
		auxTex=4;
	((Item*)this)->setIcon("icpe_charging_re_battery",auxTex);
	return Item::getIcon(auxTex,i,b);
}
unsigned int ChargingREBatteryItem::getIVoltage()const
{
	return 32;
}
unsigned int ChargingREBatteryItem::getOVoltage()const
{
	return 32;
}
