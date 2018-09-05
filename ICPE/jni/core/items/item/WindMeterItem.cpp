#include "WindMeterItem.h"

#include <stdlib.h>

#include "mcpe/item/ItemInstance.h"
#include "mcpe/block/Block.h"
#include "mcpe/entity/player/Player.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/level/Level.h"
#include "mcpe/util/FullBlock.h"
#include "mcpe/util/Util.h"
#include "mcpe/client/resources/I18n.h"
#include "mcpe/util/Random.h"

#include "blocks/Blocks.h"
#include "items/Items.h"
#include "ui/renderer/WindMeterRenderer.h"
#include "ICPE.h"

WindMeterItem::WindMeterItem():EnergyStorageItem("wind_meter",IC::Items::ID::mWindMeter-0x100)
{
	setIcon("icpe_wind_meter",0);
	setCategory(CreativeItemCategory::TOOLS);
	setHandEquipped();
}
unsigned long WindMeterItem::getMaxEnergy()const
{
	return 1E4;
}
unsigned int WindMeterItem::getIVoltage()const
{
	return 5;
}
bool WindMeterItem::use(ItemInstance&item, Player&p)const
{
	if(!hasEnergy(item,25))
		return Item::use(item, p);
	costEnergy(item,25);
	/*
	Random&r =ICPE::mRandom;
	Random& random2=p.getLevel().getRandom();
	float const maxWindLevel=130+(random2.nextFloat(5)*(random2.nextBool()?1:-1))+(r.nextFloat(0.75)*(r.nextBool()?1:-1));
	float const distance=abs(maxWindLevel-p.getPos().y);
	float const levelMaxWind=50+random2.nextFloat(5);
	float ret=levelMaxWind-(distance*0.4);
	if(ret<0)
		ret=0;
	WindMeterRenderer * windMeterMessage=new WindMeterRenderer(*ICPE::pMinecraftGame,ret);
	windMeterMessage->show();
	return Item::use(item, p);*/
	
}
std::string WindMeterItem::getInteractText(Player const&) const
{
	if(I18n::get("key.use").find("/")!=std::string::npos)
		return I18n::get("key.use").substr(0,I18n::get("key.use").find("/"));
	return I18n::get("key.use");
}
bool WindMeterItem::requiresInteract() const
{
	return true;
}
