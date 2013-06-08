#include "stdafx.h"
#include "GameItemType.h"

GameItemType::GameItemType(void)
	:GameEntityType(),
	m_type(NULL),
	m_class(GameItemClassID::None)
{
}

GameItemType::GameItemType(GameItemType&& other)
	:GameEntityType(std::move(other)),
	m_type(std::move(other.m_type)),
	m_class(std::move(other.m_class))
{
}

GameItemType& GameItemType::operator=(GameItemType&& other)
{
	GameEntityType::operator=(static_cast<GameEntityType&&>(other));
	m_type = std::move(other.m_type);
	m_class = std::move(other.m_class);
	return *this;
}

GameItemType::~GameItemType(void)
{
}

//getters
GameItemTypeID GameItemType::getTypeID(void) const
{
	return m_type;
}
GameItemClassID::E GameItemType::getClassID(void) const 
{
	return m_class;
}
//setters
void GameItemType::setTypeID(GameItemTypeID lType) 
{
	m_type = lType;
}
void GameItemType::setClassID(GameItemClassID::E lClass)
{
	m_class = lClass;
}
