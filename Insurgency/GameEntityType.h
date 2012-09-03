#pragma once
#include <string>
#include <map>
#include <memory>
#include "EntityComponent.h"
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
	std::map<EntityComponentID, std::unique_ptr<EntityComponent>> cloneComponents(void) const 
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
	void setLName(std::string str) {lName = str;}
	void setSName(std::string str) {sName = str;}

	void addComponent(std::unique_ptr<EntityComponent> lComponent, EntityComponentID lType) 
	{m_components[lType] = std::move(lComponent);}

private:
	std::string lName;
	std::string sName;
	std::map<EntityComponentID, std::unique_ptr<EntityComponent>> m_components;
};