#pragma once

#include "ICMachineBlockEntity.h"

class IronFurnaceBlockEntity : public ICMachineBlockEntity
{
private:
	bool isLit_;
	float burnProgress;
	int fireProgress;
	int maxFireProgress;
public:
	IronFurnaceBlockEntity(BlockPos const&);
	~IronFurnaceBlockEntity()=default;
public:
	virtual void load(mca::CompoundTag const&);
	virtual void save(mca::CompoundTag &)const;
	virtual void tick(Level&,unsigned long long);
public:
	bool canPushInItem(int,ItemInstance const&);
	bool isLit()const;
	void setLit(bool);
	float getBurnProgress()const;
	float getFireProgress()const;
	bool canBurn();
	bool canStartNextFire();
	int getBurnDuration(ItemInstance const*)const;
public:
	static const float mSpeed;
};
