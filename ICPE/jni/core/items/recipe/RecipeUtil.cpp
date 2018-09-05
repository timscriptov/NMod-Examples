#include "./RecipeUtil.h"

RecipeUtil::RecipeUtil()
{
	r = 0;
	fr = 0;
}
RecipeUtil::RecipeUtil(Recipes *r,FurnaceRecipes *fr)
{
	this -> r = r;
	this -> fr = fr;
}
void RecipeUtil::init(Recipes *r,FurnaceRecipes *fr)
{
	this -> r = r;
	this -> fr = fr;
}
void RecipeUtil::addRecipeTypeAuxValue(short id,short aux,char letter)
{
	Recipes::Type type;
	type.item = 0;
	type.block = 0;
	type.c = letter;
	type.inst = ItemInstance(id,1,aux);
	this -> ingredients.push_back(type);
}
void RecipeUtil::addRecipeType(short id,char letter)
{
	Recipes::Type type;
	type.item = Item::mItems[id];
	type.block = 0;
	type.c = letter;
	type.inst = ItemInstance();
	this -> ingredients.push_back(type);
}
void RecipeUtil::addFurnaceRecipe(short id,short idaux,short toId,short toaux)
{
	ItemInstance const i(toId,1,toaux);
	fr -> addFurnaceRecipeAuxData(id,idaux,i);
}
void RecipeUtil::addFurnaceRecipe(short id,short toId,short toaux)
{
	ItemInstance const i(toId,1,toaux);
	fr -> addFurnaceRecipe(id,i);
}
void RecipeUtil::addShapelessRecipe(ItemInstance const&res)
{
	r -> addShapelessRecipe(res,ingredients);
}
void RecipeUtil::addShapedRecipe(ItemInstance const & res,std::vector<std::string> const&v)
{
	r -> addShapedRecipe(res,v,ingredients);
}
void RecipeUtil::clearAllRecipeTypes()
{
	ingredients.clear();
}
