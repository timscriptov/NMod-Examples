#include "CompressorRecipes.h"

CompressorRecipes* CompressorRecipes::mInstance=0;

CompressorRecipes* CompressorRecipes::getInstance()
{
	return mInstance;
}
void CompressorRecipes::initInstance()
{
	static CompressorRecipes instance;
	instance=CompressorRecipes();
	mInstance=&instance;
}
int CompressorRecipes::getFromCount(ItemInstance const*item)
{
	if(!item||item->isNull())
		return 0;
	for(CompressorRecipe recipe:recipes)
	{
		if(recipe.from.getId()==item->getId()&&(recipe.aux==item->aux||recipe.aux==-1))
			return recipe.from.count;
	}
	return 0;
}
bool CompressorRecipes::isCompressorItem(ItemInstance const*item)const
{
	return !getResult(item).isNull();
}
ItemInstance CompressorRecipes::getResult(ItemInstance const*item)const
{
	if(!item||item->isNull())
		return ItemInstance();
	for(CompressorRecipe recipe:recipes)
	{
		if(recipe.from.getId()==item->getId()&&(recipe.aux==item->aux||recipe.aux==-1)&&item->count>=recipe.from.count)
			return recipe.result;
	}
	return ItemInstance();
}
void CompressorRecipes::addCompressorRecipe(ItemInstance const&from,int aux,ItemInstance const&result)
{
	CompressorRecipe recipe={from,aux,result};
	recipes.emplace_back(recipe);
}
