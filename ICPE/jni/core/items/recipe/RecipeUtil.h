#pragma once

#include <string>
#include <sstream>

#include "mcpe/recipe/Recipes.h"
#include "mcpe/recipe/FurnaceRecipes.h"
#include "mcpe/item/ItemInstance.h"
#include "mcpe/item/Item.h"
#include "mcpe/block/Block.h"

class RecipeUtil
{
private:
	Recipes *r;
	FurnaceRecipes *fr;
	std::vector<Recipes::Type> ingredients;
public:
	RecipeUtil();
	~RecipeUtil()=default;
	RecipeUtil(Recipes *,FurnaceRecipes *);
public:
	void init(Recipes *,FurnaceRecipes *);
	void addRecipeType(short itemId,char letter);
	void addRecipeTypeAuxValue(short itemId,short itemAux,char letter);
	void addFurnaceRecipe(short id,short aux,short toId,short toAux);
	void addFurnaceRecipe(short id,short toId,short toAux);
	void addShapedRecipe(ItemInstance const & ,std::vector<std::string> const&);
	void addShapelessRecipe(ItemInstance const&);
	void clearAllRecipeTypes();
};
