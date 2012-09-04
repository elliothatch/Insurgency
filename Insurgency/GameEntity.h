#pragma once
#include <map>
#include "EntityComponent.h"
#include "EntityComponentEnum.h"
class GameEntity
{
public:

	GameEntity();

	virtual ~GameEntity(void);

	//getters
	std::pair<int,int> getLocation(void) const;
	bool getIsEnclosed(void) const;
	std::string getLName(void) const;
	std::string getSName(void) const;
	EntityComponent* getComponent(EntityComponentID index) const;
	int getNumComponents(void) const;
	//setters
	void setLocation(std::pair<int,int> loc);
	void setIsEnclosed(bool b);
	void setLName(std::string str);
	void setSName(std::string str);
	void addComponent(std::unique_ptr<EntityComponent> lComponent, EntityComponentID lType);

private:
	bool m_isEnclosed; //is in creature inventory, in a box, etc. Cannot determine own position
	std::pair<int,int> m_location;
	std::string m_lName;
	std::string m_sName;
protected:
	std::map<EntityComponentID, std::unique_ptr<EntityComponent>> m_components;

};