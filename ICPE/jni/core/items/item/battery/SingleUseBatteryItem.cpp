#include "SingleUseBatteryItem.h"

SingleUseBatteryItem::SingleUseBatteryItem():DischargeableEnergyStorageItem("single_use_battery",ID::mSingleUseBattery-0x100)
{
	setIcon("icpe_single_use_battery",0);
}
unsigned long SingleUseBatteryItem::getMaxEnergy()const
{
	return 1200;
}
bool SingleUseBatteryItem::canCharge()const
{
	return false;
}
unsigned int SingleUseBatteryItem::getOVoltage()const
{
	return 5;
}
