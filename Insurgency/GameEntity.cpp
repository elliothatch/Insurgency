#include "stdafx.h"
#include "GameEntity.h"

GameEntity::GameEntity(std::pair<int,int> loc)
		:location(loc),
		lName("lNameE"),
		sName("sNameE")
{
}

GameEntity::~GameEntity()
{
}

//getters
std::pair<int,int> GameEntity::getLocation(void) const 
{
	return location;
}

std::string  GameEntity::getLName(void) const
{
	return lName;
}
std::string GameEntity::getSName(void) const 
{
	return sName;
}
EntityComponent* GameEntity::getComponent(EntityComponentID index) const
{
	if(m_components.at(index))
		return m_components.at(index).get();
	else
		return NULL;
}
int GameEntity::getNumComponents(void) const
{
	return m_components.size();
}
//setters
void GameEntity::setLocation(std::pair<int,int> loc)
{
	location = loc;
}

void GameEntity::setLName(std::string str) 
{
	lName = str;
}

void GameEntity::setSName(std::string str) 
{
	sName = str;
}

void GameEntity::addComponent(std::unique_ptr<EntityComponent> lComponent, EntityComponentID lType)
{
	m_components[lType] = std::move(lComponent);
}