#include <jni.h>
#include "Substrate.h"
#include "mcpe.h"

static int (*_Recipes_init)(Recipes*);
static int Recipes_init(Recipes* thiz) {
    _Recipes_init(thiz);
    
    ItemInstance* myInst = new ItemInstance(*Item::mNewApple_enchanted, 1);
    
    const std::string& myStr1 = "###";
    const std::string& myStr2 = "#O#";
    
    const std::vector<Recipes::Type, std::allocator<Recipes::Type>>& myDef = 
    definition<Block const*, VanillaItem*>('#', Block::mNewGoldBlock, 'O', VanillaItem::mNewApple);
    
    thiz->addShapedRecipe(*myInst, myStr1, myStr2, myStr1, myDef);
}

JNIEXPORT jint JNI_OnLoad(JavaVM*vm,void*)
{
	MSHookFunction((void*)&Recipes::init, (void*)&Recipes_init, (void**)&_Recipes_init);
	return JNI_VERSION_1_6;
}
