#include "stdafx.h"
#include "GameItemType.h"

GameItemType::GameItemType(void)
	:GameEntityType(),
	m_type(NULL),
	m_class(GameItemClass_NoClass)
{
}

GameItemType::~GameItemType(void)
{
}

//getters
GameItemTypeID GameItemType::getTypeID(void) const
{
	return m_type;
}
GameItemClassID GameItemType::getClassID(void) const 
{
	return m_class;
}
//setters
void GameItemType::setTypeID(GameItemTypeID lType) 
{
	m_type = lType;
}
void GameItemType::setClassID(GameItemClassID lClass)
{
	m_class = lClass;
}
