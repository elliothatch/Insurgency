#pragma once
#include <map>
#include "EntityComponent.h"
class GameEntity
{
public:

	//GameEntity();
	GameEntity(std::map<EntityComponentID::E, std::unique_ptr<EntityComponent>> lComponents);
	GameEntity(const std::string& lLName, const std::string& lSName, const std::string& lDName,
		std::map<EntityComponentID::E, std::unique_ptr<EntityComponent>> lComponents);
	virtual ~GameEntity(void);

	//getters
	std::pair<int,int> getLocation(void) const;
	GameEntity* getEnclosingEntity(void) const;
	const std::string& getLName(void) const;
	const std::string& getSName(void) const;
	const std::string& getDName(void) const;
	EntityComponent* getComponent(EntityComponentID::E index) const;
	int getNumComponents(void) const;
	//setters
	void setLocation(std::pair<int,int> loc);
	void setEnclosingEntity(GameEntity* lEntity);
	void setLName(const std::string& str);
	void setSName(const std::string& str);
	void setDName(const std::string& str);
	void addComponent(std::unique_ptr<EntityComponent> lComponent);

private:
	GameEntity* m_enclosingEntity; //is in creature inventory, in a box, etc. Cannot determine own position
	std::pair<int,int> m_location;
	std::string m_lName;
	std::string m_sName;
	std::string m_dName;
protected:
	std::map<EntityComponentID::E, std::unique_ptr<EntityComponent>> m_components;

};