#include "stdafx.h"
#include "GameEntity.h"

/*
GameEntity::GameEntity()
		:m_location(std::pair<int,int>(0,0)),
		m_lName("lNameE"),
		m_sName("sNameE"),
		m_isEnclosed(false)
{
}
*/

GameEntity::GameEntity(std::map<EntityComponentID::E, std::unique_ptr<EntityComponent>> lComponents)
		:m_components(std::move(lComponents)),
		m_location(std::pair<int,int>(0,0)),
		m_lName("lNameE"), m_sName("sNameE"), m_dName("dNameE"),
		m_isEnclosed(false)
{
}
GameEntity::GameEntity(const std::string& lLName, const std::string& lSName, const std::string& lDName,
	std::map<EntityComponentID::E, std::unique_ptr<EntityComponent>> lComponents)
		:m_components(std::move(lComponents)),
		m_location(std::pair<int,int>(0,0)),
		m_lName(lLName), m_sName(lSName), m_dName(lDName),
		m_isEnclosed(false)
{
}

GameEntity::~GameEntity()
{
}

//getters
std::pair<int,int> GameEntity::getLocation(void) const 
{
	return m_location;
}
bool GameEntity::getIsEnclosed(void) const
{
	return m_isEnclosed;
}
const std::string&  GameEntity::getLName(void) const
{
	return m_lName;
}
const std::string& GameEntity::getSName(void) const 
{
	return m_sName;
}
const std::string& GameEntity::getDName(void) const
{
	return m_dName;
}
EntityComponent* GameEntity::getComponent(EntityComponentID::E index) const
{
	if(m_components.find(index) != m_components.end())
		return m_components.at(index).get();
	else
		return nullptr;
}
int GameEntity::getNumComponents(void) const
{
	return m_components.size();
}
//setters
void GameEntity::setLocation(std::pair<int,int> loc)
{
	m_location = loc;
}
void GameEntity::setIsEnclosed(bool b)
{
	m_isEnclosed = b;
}
void GameEntity::setLName(const std::string& str) 
{
	m_lName = str;
}

void GameEntity::setSName(const std::string& str) 
{
	m_sName = str;
}
void GameEntity::setDName(const std::string& str)
{
	m_dName = str;
}
void GameEntity::addComponent(std::unique_ptr<EntityComponent> lComponent)
{
	m_components[lComponent->getType()] = std::move(lComponent);
}