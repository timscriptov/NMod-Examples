#pragma once

#include <vector>
#include "mcpe/item/ItemInstance.h"

class MaceratorRecipes
{
private:
	struct MaceratorRecipe
	{
		unsigned short id;
		int aux;
		ItemInstance result;
	};
	std::vector<MaceratorRecipe> recipes;
public:
	static MaceratorRecipes* mInstance;
	static MaceratorRecipes* getInstance();
	static void initInstance();
public:
	MaceratorRecipes()=default;
	~MaceratorRecipes()=default;
public:
	bool isMaceratorItem(ItemInstance const*)const;
	ItemInstance getResult(ItemInstance const*)const;
	void addMaceratorRecipe(unsigned short,int,ItemInstance const&);
};
