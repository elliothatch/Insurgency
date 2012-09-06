#include "StdAfx.h"
#include "GameItem.h"


GameItem::GameItem(const GameItemType& lItemType)
	:GameEntity(lItemType.getLName(), lItemType.getSName(), std::move(lItemType.cloneComponents())),
	m_type(lItemType.getTypeID()),
	m_class(lItemType.getClassID())
{
}


GameItem::~GameItem(void)
{
}

GameItemTypeID GameItem::getType(void) const 
{
	return m_type;
}

GameItemClassID::E GameItem::getClass(void) const
{
	return m_class;
}