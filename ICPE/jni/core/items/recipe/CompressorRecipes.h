#pragma once

#include <vector>
#include "mcpe/item/ItemInstance.h"

class CompressorRecipes
{
private:
	struct CompressorRecipe
	{
		ItemInstance from;
		int aux;
		ItemInstance result;
	};
	std::vector<CompressorRecipe> recipes;
public:
	static CompressorRecipes* mInstance;
	static CompressorRecipes* getInstance();
	static void initInstance();
public:
	CompressorRecipes()=default;
	~CompressorRecipes()=default;
public:
	bool isCompressorItem(ItemInstance const*)const;
	ItemInstance getResult(ItemInstance const*)const;
	int getFromCount(ItemInstance const*);
	void addCompressorRecipe(ItemInstance const&,int,ItemInstance const&);
};
