#pragma once
#include <map>
#include "EntityComponent.h"
#include "EntityComponentEnum.h"
class GameEntity
{
public:

	GameEntity(std::pair<int,int> loc);

	virtual ~GameEntity(void);

	//getters
	std::pair<int,int> getLocation(void) const;
	std::string getLName(void) const;
	std::string getSName(void) const;
	EntityComponent* getComponent(EntityComponentID index) const;
	int getNumComponents(void) const;
	//setters
	void setLocation(std::pair<int,int> loc);
	void setLName(std::string str);
	void setSName(std::string str);
	void addComponent(std::unique_ptr<EntityComponent> lComponent, EntityComponentID lType);

private:
	std::pair<int,int> location;
	std::string lName;
	std::string sName;
protected:
	std::map<EntityComponentID, std::unique_ptr<EntityComponent>> m_components;

};