#include "CEntityBlock.h"

CEntityBlock::CEntityBlock(std::string const&name,short id,Material const&material)
:EntityBlock(name,id,material)
{
	(*(BlockEntityType*)(((void*)this)+28))=(BlockEntityType)100;
}
