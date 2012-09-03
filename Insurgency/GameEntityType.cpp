#include "stdafx.h"
#include "GameEntityType.h"

GameEntityType::GameEntityType(void)
	:m_lName("lName"), m_sName("sName")
{
}

GameEntityType::~GameEntityType(void)
{
}

//getters
std::string GameEntityType::getLName(void) const 
{
	return m_lName;
}
std::string GameEntityType::getSName(void) const 
{
	return m_sName;
}
std::map<EntityComponentID, std::unique_ptr<EntityComponent>> GameEntityType::cloneComponents(void) const 
{
	std::map<EntityComponentID, std::unique_ptr<EntityComponent>> retComps;
	for(std::map<EntityComponentID, std::unique_ptr<EntityComponent>>::const_iterator compIt(m_components.begin());
		compIt != m_components.end(); compIt++)
	{
		retComps[compIt->first] = std::unique_ptr<EntityComponent>(compIt->second->clone());
	}
	return std::move(retComps);
}
//setters
void GameEntityType::setLName(std::string str)
{
	m_lName = str;
}
void GameEntityType::setSName(std::string str)
{
	m_sName = str;
}
void GameEntityType::addComponent(std::unique_ptr<EntityComponent> lComponent, EntityComponentID lType) 
{
	m_components[lType] = std::move(lComponent);
}
