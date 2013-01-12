#include "stdafx.h"
#include "GameEntity.h"

#include "InventoryComponent.h"
#include "EquipSlotsComponent.h"
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
		m_enclosingEntity(nullptr),
		m_actions()
{
	for(std::map<EntityComponentID::E, std::unique_ptr<EntityComponent>>::iterator entityIt(m_components.begin());
			entityIt != m_components.end(); entityIt++)
	{
		entityIt->second->setEntity(*this);
	}
}
GameEntity::GameEntity(const std::string& lLName, const std::string& lSName, const std::string& lDName,
	std::map<EntityComponentID::E, std::unique_ptr<EntityComponent>> lComponents, GameEntityActions lActions)
		:m_components(std::move(lComponents)),
		m_location(std::pair<int,int>(0,0)),
		m_lName(lLName), m_sName(lSName), m_dName(lDName),
		m_enclosingEntity(nullptr),
		m_actions(lActions)
{
	for(std::map<EntityComponentID::E, std::unique_ptr<EntityComponent>>::iterator entityIt(m_components.begin());
			entityIt != m_components.end(); entityIt++)
	{
		entityIt->second->setEntity(*this);
	}
}

GameEntity::~GameEntity()
{
}

bool GameEntity::canEquipEntity(const GameEntity& target) const
{
	//empty virtual implementation
	return false;
}

//getters
std::pair<int,int> GameEntity::getLocation(void) const 
{
	return m_location;
}
GameEntity* GameEntity::getEnclosingEntity(void) const
{
	return m_enclosingEntity;
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
void GameEntity::setEnclosingEntity(GameEntity* lEntity)
{
	m_enclosingEntity = lEntity;
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

void GameEntity::setGameEntityActions(GameEntityActions actions)
{
	m_actions = actions;
}
GameEntityActions GameEntity::getGameEntityActions() const
{
	return m_actions;
}

std::set<EntityActionID::E> GameEntity::getPerformableActions(GameEntity* target) const
{
	std::set<EntityActionID::E> returnSet;
	if(target->getEnclosingEntity() == nullptr) //target is in the world
	{
		//check for stuff
		returnSet = target->getGameEntityActions().getWorldActions();
	}
	if(target->getEnclosingEntity() == this) //it is in my possession
	{
		//in my inventory
		if(InventoryComponent* invComponent = dynamic_cast<InventoryComponent*>(getComponent(EntityComponentID::Inventory)))
		{
			returnSet = target->getGameEntityActions().getInventoryActions();
			//check what I can do
		}
		//equipped
		else if(EquipSlotsComponent* equipComponent = dynamic_cast<EquipSlotsComponent*>(getComponent(EntityComponentID::EquipSlots)))
		{
			if(equipComponent->isEntityEquipped(*target))
			{
				//check what I can do
				returnSet = target->getGameEntityActions().getEquippedActions();
			}
		}
	}
	return returnSet;
}
