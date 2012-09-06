#include "StdAfx.h"
#include "GameItem.h"


GameItem::GameItem(const GameItemType& lItemType)
	:GameEntity(),
	m_type(lItemType.getTypeID()),
	m_class(lItemType.getClassID())
{
	setLName(lItemType.getLName());
	setSName(lItemType.getSName());
	m_components = lItemType.cloneComponents();
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