#include "ExtractorRecipes.h"

ExtractorRecipes* ExtractorRecipes::mInstance=0;

ExtractorRecipes* ExtractorRecipes::getInstance()
{
	return mInstance;
}
void ExtractorRecipes::initInstance()
{
	static ExtractorRecipes instance;
	instance=ExtractorRecipes();
	mInstance=&instance;
}
bool ExtractorRecipes::isExtractorItem(ItemInstance const*item)const
{
	return !getResult(item).isNull();
}
ItemInstance ExtractorRecipes::getResult(ItemInstance const*item)const
{
	if(!item||item->isNull())
		return ItemInstance();
	for(ExtractorRecipe recipe:recipes)
	{
		if(recipe.id==item->getId()&&(recipe.aux==item->aux||recipe.aux==-1))
			return recipe.result;
	}
	return ItemInstance();
}
void ExtractorRecipes::addExtractorRecipe(unsigned short id,int aux,ItemInstance const&result)
{
	ExtractorRecipe recipe={id,aux,result};
	recipes.emplace_back(recipe);
}
