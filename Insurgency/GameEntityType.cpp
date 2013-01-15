#include "stdafx.h"
#include "GameEntityType.h"

GameEntityType::GameEntityType(void)
	:m_lName("lName"), m_sName("sName"), m_dName("dName"),
	 m_actions(), m_equipGroups()
{
}

GameEntityType::~GameEntityType(void)
{
}

//getters
const std::string& GameEntityType::getLName(void) const 
{
	return m_lName;
}
const std::string& GameEntityType::getSName(void) const 
{
	return m_sName;
}

const std::string& GameEntityType::getDName(void) const
{
	return m_dName;
}
std::map<EntityComponentID::E, std::unique_ptr<EntityComponent>> GameEntityType::cloneComponents(void) const 
{
	std::map<EntityComponentID::E, std::unique_ptr<EntityComponent>> retComps;
	for(std::map<EntityComponentID::E, std::unique_ptr<EntityComponent>>::const_iterator compIt(m_components.begin());
		compIt != m_components.end(); compIt++)
	{
		retComps[compIt->first] = std::unique_ptr<EntityComponent>(compIt->second->clone());
	}
	return retComps;
}
//setters
void GameEntityType::setLName(const std::string& str)
{
	m_lName = str;
}
void GameEntityType::setSName(const std::string& str)
{
	m_sName = str;
}
void GameEntityType::setDName(const std::string& str)
{
	m_dName = str;
}
void GameEntityType::addComponent(std::unique_ptr<EntityComponent> lComponent) 
{
	m_components[lComponent->getType()] = std::move(lComponent);
}

void GameEntityType::setGameEntityActions(GameEntityActions actions)
{
	m_actions = actions;
}
GameEntityActions GameEntityType::getGameEntityActions() const
{
	return m_actions;
}
void GameEntityType::setGameEntityEquipGroups(GameEntityEquipGroups equipGroups)
{
	m_equipGroups = equipGroups;
}
GameEntityEquipGroups GameEntityType::getGameEntityEquipGroups() const
{
	return m_equipGroups;
}