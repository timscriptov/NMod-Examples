#pragma once

#include <vector>

#include "ICBlockEntity.h"
#include "mcpe/item/ItemInstance.h"

class ContainerBlockEntity : public ICBlockEntity
{
protected:
	int const slotsCount;
	std::vector<ItemInstance>slots;
public:
	ContainerBlockEntity(BlockPos const&,int);
	~ContainerBlockEntity()=default;
public:
	virtual void onSlotChanged(int);
	virtual void addItem(int,short);
	virtual bool isEmptySlot(int);
	virtual ItemInstance* getSlot(int);
	virtual void setSlot(int,ItemInstance const*);
	virtual void costItem(int,short);
	virtual void load(mca::CompoundTag const&);
	virtual void save(mca::CompoundTag &)const;
	virtual void remove();
	virtual void reset();
};
