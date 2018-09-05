#include "REBatteryItem.h"

#include <math.h>

REBatteryItem::REBatteryItem():EnergyStorageItem("re_battery",ID::mReBattery-0x100)
{
	setCategory(CreativeItemCategory::TOOLS);
	setMaxStackSize(1);
	setStackedByData(true);
}
unsigned long REBatteryItem::getMaxEnergy()const
{
	return 1E4;
}
TextureUVCoordinateSet const& REBatteryItem::getIcon(int aux, int i, bool b) const
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
	((Item*)this)->setIcon("icpe_re_battery",auxTex);
	return Item::getIcon(auxTex,i,b);
}
unsigned int REBatteryItem::getIVoltage()const
{
	return 10;
}
unsigned int REBatteryItem::getOVoltage()const
{
	return 10;
}
