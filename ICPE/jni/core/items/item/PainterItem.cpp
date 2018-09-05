#include "PainterItem.h"

#include "mcpe/client/resources/I18n.h"
#include "mcpe/util/Util.h"
#include "mcpe/entity/Mob.h"
#include "mcpe/entity/EntityType.h"
#include "mcpe/entity/EntityClassTree.h"
#include "mcpe/entity/player/Player.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/block/Block.h"
#include "blocks/blockentity/CableBlockEntity.h"
#include "blocks/blocks.h"
#include "items/PainterAux.h"
#include "util/CableUtil.h"
#include "util/ItemUtils.h"

PainterItem::PainterItem():IC::Items("painter",Items::ID::mPainter-0x100)
{
	setCategory(CreativeItemCategory::TOOLS);
	setMaxStackSize(1);
	setStackedByData(true);
	setHandEquipped();
}
bool PainterItem::_useOn(ItemInstance&item, Entity&ent, BlockPos pos, signed char, float, float, float)const
{
	PaletteColor colorType;
	switch((short)item.getAuxValue()%17)
	{
	case (short)PainterAux::WHITE:
		colorType=PaletteColor::WHITE;
	break;
	case (short)PainterAux::ORANGE:
		colorType=PaletteColor::ORANGE;
	break;
	case (short)PainterAux::MAGENTA:
		colorType=PaletteColor::MAGENTA;
	break;
	case (short)PainterAux::LIGHTBLUE:
		colorType=PaletteColor::LIGHTBLUE;
	break;
	case (short)PainterAux::YELLOW:
		colorType=PaletteColor::YELLOW;
	break;
	case (short)PainterAux::LIME:
		colorType=PaletteColor::LIME;
	break;
	case (short)PainterAux::PINK:
		colorType=PaletteColor::PINK;
	break;
	case (short)PainterAux::BROWN:
		colorType=PaletteColor::BROWN;
	break;
	case (short)PainterAux::CYAN:
		colorType=PaletteColor::CYAN;
	break;
	case (short)PainterAux::GRAY:
		colorType=PaletteColor::GRAY;
	break;
	case (short)PainterAux::RED:
		colorType=PaletteColor::RED;
	break;
	case (short)PainterAux::GREEN:
		colorType=PaletteColor::GREEN;
	break;
	case (short)PainterAux::BLUE:
		colorType=PaletteColor::BLUE;
	break;
	case (short)PainterAux::PURPLE:
		colorType=PaletteColor::PURPLE;
	break;
	case (short)PainterAux::LIGHTGRAY:
		colorType=PaletteColor::LIGHTGRAY;
	break;
	case (short)PainterAux::BLACK:
		colorType=PaletteColor::BLACK;
	break;
	default:
		return false;
	}

	if(ent.getRegion().getBlock(pos)==Block::mBlocks[35])
		ent.getRegion().setBlockAndData(pos,35,(unsigned char)colorType,3,0);
	else if(ent.getRegion().getBlock(pos)==Block::mBlocks[171])
		ent.getRegion().setBlockAndData(pos,171,(unsigned char)colorType,3,0);
	else if(ent.getRegion().getBlock(pos)==Block::mBlocks[172])
		ent.getRegion().setBlockAndData(pos,159,(unsigned char)colorType,3,0);
	else if(ent.getRegion().getBlock(pos)==Block::mBlocks[159])
		ent.getRegion().setBlockAndData(pos,159,(unsigned char)colorType,3,0);
	else if(ent.getRegion().getBlock(pos)==Block::mBlocks[IC::Blocks::ID::mCable]&&CableUtil::canDye(ent.getRegion().getData(pos)))
		((CableBlockEntity*)ent.getRegion().getBlockEntity(pos))->setColor((unsigned char)colorType);
	else
		return false;
	
	if((item.getAuxValue()-item.getAuxValue()%17)<(17*32))
		item.aux+=17;
	if((item.getAuxValue()-item.getAuxValue()%17)>=(17*32))
		item.aux=16;
	return false;
}
std::string PainterItem::buildEffectDescriptionName(ItemInstance const&i) const
{
	if(i.getAuxValue()%17!=16)
		return "§7"+I18n::get("item.ItemTool.tooltip.UsesLeft")+Util::toString(32-(i.getAuxValue()-i.getAuxValue()%17)/17)+"/32";
	return Item::buildEffectDescriptionName(i);
}
void PainterItem::interactEnemy(ItemInstance&item, Mob*mob, Player*player)const
{
	if(!mob||!player)
		return;
	PaletteColor colorType;
	switch((short)item.getAuxValue()%17)
	{
	case (short)PainterAux::WHITE:
		colorType=PaletteColor::WHITE;
	break;
	case (short)PainterAux::ORANGE:
		colorType=PaletteColor::ORANGE;
	break;
	case (short)PainterAux::MAGENTA:
		colorType=PaletteColor::MAGENTA;
	break;
	case (short)PainterAux::LIGHTBLUE:
		colorType=PaletteColor::LIGHTBLUE;
	break;
	case (short)PainterAux::YELLOW:
		colorType=PaletteColor::YELLOW;
	break;
	case (short)PainterAux::LIME:
		colorType=PaletteColor::LIME;
	break;
	case (short)PainterAux::PINK:
		colorType=PaletteColor::PINK;
	break;
	case (short)PainterAux::BROWN:
		colorType=PaletteColor::BROWN;
	break;
	case (short)PainterAux::CYAN:
		colorType=PaletteColor::CYAN;
	break;
	case (short)PainterAux::GRAY:
		colorType=PaletteColor::GRAY;
	break;
	case (short)PainterAux::RED:
		colorType=PaletteColor::RED;
	break;
	case (short)PainterAux::GREEN:
		colorType=PaletteColor::GREEN;
	break;
	case (short)PainterAux::BLUE:
		colorType=PaletteColor::BLUE;
	break;
	case (short)PainterAux::PURPLE:
		colorType=PaletteColor::PURPLE;
	break;
	case (short)PainterAux::LIGHTGRAY:
		colorType=PaletteColor::LIGHTGRAY;
	break;
	case (short)PainterAux::BLACK:
		colorType=PaletteColor::BLACK;
	break;
	default:
		return;
	}
	
	mob->setColor(colorType);
	
	if(player->isCreative())
		return;
	if((item.getAuxValue()-item.getAuxValue()%17)<(17*32))
		item.aux+=17;
	if((item.getAuxValue()-item.getAuxValue()%17)>=(17*32))
		item.aux=16;
}
TextureUVCoordinateSet const& PainterItem::getIcon(int aux, int i, bool b) const
{
	((Item*)this)->setIcon("icpe_painter_item",aux%17);
	return Item::getIcon(aux%17,i,b);
}
