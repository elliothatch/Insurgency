#pragma once
#include <string>
#include <map>
class EntityComponent;
#include "EntityComponentEnum.h"
class GameEntityType
{
public:

	GameEntityType(void)
	{
		lName = "lName";
		sName = "sName";
	}

	virtual ~GameEntityType(void)
	{
	}

	//getters
	std::string getLName(void) const {return lName;}
	std::string getSName(void) const {return sName;}
	std::map<EntityComponentID, EntityComponent*> getComponents(void) const {return m_components;}
	//setters
	void setLName(std::string str) {lName = str;}
	void setSName(std::string str) {sName = str;}

	void addComponent(EntityComponent* lComponent, EntityComponentID lType) {m_components[lType] = lComponent;}

private:
	std::string lName;
	std::string sName;
	std::map<EntityComponentID, EntityComponent*> m_components;
};

