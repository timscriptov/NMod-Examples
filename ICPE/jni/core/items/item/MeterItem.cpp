#include "MeterItem.h"

#include "mcpe/util/BlockPos.h"

#include "ICPE.h"
#include "ui/renderer/EUMeterRenderer.h"

MeterItem::MeterItem():IC::Items("meter",Items::ID::mMeter-0x100)
{
	setCategory(CreativeItemCategory::TOOLS);
	setMaxStackSize(1);
	setIcon("icpe_meter",0);
}
bool MeterItem::_useOn(ItemInstance&, Entity&, BlockPos pos, signed char, float, float, float)const
{
	//EUMeterRenderer *euMeter=new EUMeterRenderer(*ICPE::pMinecraftGame);
	//euMeter->show();
}
