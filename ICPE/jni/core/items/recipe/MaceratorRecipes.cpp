#include "MaceratorRecipes.h"

MaceratorRecipes* MaceratorRecipes::mInstance=0;

MaceratorRecipes* MaceratorRecipes::getInstance()
{
	return mInstance;
}
void MaceratorRecipes::initInstance()
{
	static MaceratorRecipes instance;
	instance=MaceratorRecipes();
	mInstance=&instance;
}
bool MaceratorRecipes::isMaceratorItem(ItemInstance const*item)const
{
	return !getResult(item).isNull();
}
ItemInstance MaceratorRecipes::getResult(ItemInstance const*item)const
{
	if(!item||item->isNull())
		return ItemInstance();
	for(MaceratorRecipe recipe:recipes)
	{
		if(recipe.id==item->getId()&&(recipe.aux==item->aux||recipe.aux==-1))
			return recipe.result;
	}
	return ItemInstance();
}
void MaceratorRecipes::addMaceratorRecipe(unsigned short id,int aux,ItemInstance const&result)
{
	MaceratorRecipe recipe={id,aux,result};
	recipes.emplace_back(recipe);
}
