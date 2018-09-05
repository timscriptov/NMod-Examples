#include "ContainerBlockEntity.h"

#include "mcpe/item/ItemInstance.h"
#include "mcpe/item/enchant/ItemEnchants.h"
#include "mcpe/item/enchant/EnchantUtils.h"
#include "mcpe/util/Util.h"
#include "mcpe/block/Block.h"

#include "mca/data/Database.h"

ContainerBlockEntity::ContainerBlockEntity(BlockPos const&pos,int count):ICBlockEntity(pos),slotsCount(count)
{
	slots=std::vector<ItemInstance>(count);
	for(ItemInstance&item:slots)
		item.setNull();
}
void ContainerBlockEntity::onSlotChanged(int)
{
	
}
void ContainerBlockEntity::reset()
{
	slots=std::vector<ItemInstance>(slotsCount);
	for(ItemInstance&item:slots)
		item.setNull();
}
void ContainerBlockEntity::remove()
{
	/*for(ItemInstance&item:slots)
	{
		if(!item.isNull())
			block->popResource(getRegion(),pos,item);
	}*/
}
void ContainerBlockEntity::addItem(int pos_,short count)
{
	if(pos_>=slotsCount||slots[pos_].isNull())
		return;
	
	slots[pos_].count+=count;
}
bool ContainerBlockEntity::isEmptySlot(int pos_)
{
	if(pos_>=slotsCount)
		return false;
	return slots[pos_].isNull();
}
ItemInstance* ContainerBlockEntity::getSlot(int pos_)
{
	if(pos_>=slotsCount)
		return NULL;
	return &(slots[pos_]);
}
void ContainerBlockEntity::setSlot(int pos_,ItemInstance const*item)
{
	if(pos_>=slotsCount)
		return;
	
	if(item==NULL||item->isNull())
		slots[pos_].setNull();
	else
	{
		ItemInstance clone=item->clone();
		slots[pos_]=clone;
	}
}
void ContainerBlockEntity::costItem(int pos_,short count)
{
	if(pos_>=slotsCount||slots[pos_].isNull())
		return;
	
	if(slots[pos_].count>count)
		slots[pos_].count-=count;
	else
		slots[pos_].setNull();
}
void ContainerBlockEntity::load(mca::CompoundTag const&tag)
{
	for(int i=0;i<slotsCount;++i)
	{
		ItemInstance item;
		
		short count=tag.getShort("containerItem_count_"+Util::toString(i));
		short id=tag.getShort("containerItem_id_"+Util::toString(i));
		short aux=tag.getShort("containerItem_aux_"+Util::toString(i));
		std::string customName=tag.getString("containerItem_customName_"+Util::toString(i));
		short repair=tag.getInt("containerItem_repair_"+Util::toString(i));
		bool hasCustomName=tag.getBool("containerItem_hasCustomName_"+Util::toString(i));
		
		item.init(id,count,aux);
		if(hasCustomName)
			item.setCustomName(customName);
		if(repair!=0)
			item.setRepairCost(repair);
		
		if(id==0)
			item.setNull();
		
		if(!item.isNull())
		{
			for(int ii=0;ii<25;++ii)
			{
				short level=tag.getShort("containerItem_enchant_"+Util::toString(i)+"_"+Util::toString(ii));
				if(level>0)
					EnchantUtils::applyEnchant(item,ii,level);
			}
		}
		slots[i]=item;
	}
}
void ContainerBlockEntity::save(mca::CompoundTag&tag)const
{
	for(int i=0;i<slotsCount;++i)
	{
		if(slots[i].isNull())
		{
			tag.putShort("containerItem_count_"+Util::toString(i),0);
			tag.putShort("containerItem_id_"+Util::toString(i),0);
			tag.putShort("containerItem_aux_"+Util::toString(i),0);
			tag.putString("containerItem_customName_"+Util::toString(i),"");
			tag.putInt("containerItem_repair_"+Util::toString(i),0);
			tag.putBool("containerItem_hasCustomName_"+Util::toString(i),false);
		}
		else
		{
			tag.putShort("containerItem_count_"+Util::toString(i),slots[i].count);
			tag.putShort("containerItem_id_"+Util::toString(i),slots[i].getId());
			tag.putShort("containerItem_aux_"+Util::toString(i),slots[i].getAuxValue());
			tag.putBool("containerItem_hasCustomName_"+Util::toString(i),slots[i].hasCustomHoverName());
			if(slots[i].hasCustomHoverName())
				tag.putString("containerItem_customName_"+Util::toString(i),slots[i].getCustomName());
			else
				tag.putString("containerItem_customName_"+Util::toString(i),"");
			tag.putInt("containerItem_repair_"+Util::toString(i),slots[i].getBaseRepairCost());
			for(int ii=0;ii<25;++ii)
			{
				if(EnchantUtils::hasEnchant(ii,slots[i]))
					tag.putShort("containerItem_enchant_"+Util::toString(i)+"_"+Util::toString(ii),EnchantUtils::getEnchantLevel(ii,slots[i]));
				else
					tag.putShort("containerItem_enchant_"+Util::toString(i)+"_"+Util::toString(ii),0);
			}
		}
	}
}
