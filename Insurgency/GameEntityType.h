#pragma once
#include <string>
#include <map>
#include <set>
#include <memory>
#include "EntityComponent.h"
#include "GameEntityActions.h"
#include "GameEntityEquipGroups.h"

class GameEntityType
{
public:

	GameEntityType(void);
	~GameEntityType(void);

	//getters
	const std::string& getLName(void) const;
	const std::string& getSName(void) const;
	const std::string& getDName(void) const;
	std::map<EntityComponentID::E, std::unique_ptr<EntityComponent>> cloneComponents(void) const;
	//setters
	void setLName(const std::string& str);
	void setSName(const std::string& str);
	void setDName(const std::string& str);

	void addComponent(std::unique_ptr<EntityComponent> lComponent);

	void setGameEntityActions(GameEntityActions actions);
	GameEntityActions getGameEntityActions() const;
	void setGameEntityEquipGroups(GameEntityEquipGroups equipGroups);
	GameEntityEquipGroups getGameEntityEquipGroups() const;

private:
	std::string m_lName; //dName + modifiers            - mutable
	std::string m_sName; //short name OR personal name  - mutable
	std::string m_dName; //Name used in Descriptions    - non-mutable
	std::map<EntityComponentID::E, std::unique_ptr<EntityComponent>> m_components;
	GameEntityActions m_actions;
	GameEntityEquipGroups m_equipGroups;
	
};