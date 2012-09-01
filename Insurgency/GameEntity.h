#pragma once
#include <map>
class EntityComponent;
#include "EntityComponentEnum.h"
class GameEntity
{
public:

	GameEntity(std::pair<int,int> loc)
		:location(loc),
		lName("lNameE"),
		sName("sNameE")
	{
	}

	virtual ~GameEntity(void)
	{
	}
	//Note: The GameEntity cannot delete the components. I think this will need to be handled in the GameWorld.

	//getters
	std::pair<int,int> getLocation(void) const {return location;}
	std::string getLName(void) const {return lName;}
	std::string getSName(void) const {return sName;}
	EntityComponent* getComponent(EntityComponentID index) const;
	int getNumComponents(void) const;
	//setters
	void setLocation(std::pair<int,int> loc) {location = loc;}
	void setLName(std::string str) {lName = str;}
	void setSName(std::string str) {sName = str;}
	void addComponent(EntityComponent* lComponent, EntityComponentID lType);
	//WARNING: IF THE SAME TYPE OF COMPONENT IS ADDED TWICE, IT *WILL* LEAK MEMORY
	//NOTE: I don't think I will need this function anyway... the components are handed in the constructor

private:
	std::pair<int,int> location;
	std::string lName;
	std::string sName;
protected:
	std::map<EntityComponentID, EntityComponent*> m_components;

};

inline EntityComponent* GameEntity::getComponent(EntityComponentID index) const
{
	if(m_components.at(index))
		return m_components.at(index);
	else
		return NULL;
}

inline int GameEntity::getNumComponents(void) const
{
	return m_components.size();
}

inline void GameEntity::addComponent(EntityComponent* lComponent, EntityComponentID lType)
{
	//if(m_components.find(lType) == m_components.end())
	m_components[lType] = lComponent;
}