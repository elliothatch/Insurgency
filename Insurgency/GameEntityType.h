#pragma once
#include <string>
#include <map>
#include <memory>
#include "EntityComponent.h"
class GameEntityType
{
public:

	GameEntityType(void);
	~GameEntityType(void);

	//getters
	std::string getLName(void) const;
	std::string getSName(void) const;
	std::map<EntityComponentID::E, std::unique_ptr<EntityComponent>> cloneComponents(void) const;
	//setters
	void setLName(std::string str);
	void setSName(std::string str);

	void addComponent(std::unique_ptr<EntityComponent> lComponent);

private:
	std::string m_lName;
	std::string m_sName;
	std::map<EntityComponentID::E, std::unique_ptr<EntityComponent>> m_components;
};