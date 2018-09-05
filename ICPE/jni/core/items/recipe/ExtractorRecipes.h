#pragma once

#include <vector>
#include "mcpe/item/ItemInstance.h"

class ExtractorRecipes
{
private:
	struct ExtractorRecipe
	{
		unsigned short id;
		int aux;
		ItemInstance result;
	};
	std::vector<ExtractorRecipe> recipes;
public:
	static ExtractorRecipes* mInstance;
	static ExtractorRecipes* getInstance();
	static void initInstance();
public:
	ExtractorRecipes()=default;
	~ExtractorRecipes()=default;
public:
	bool isExtractorItem(ItemInstance const*)const;
	ItemInstance getResult(ItemInstance const*)const;
	void addExtractorRecipe(unsigned short,int,ItemInstance const&);
};
