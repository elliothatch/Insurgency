#pragma once
#include <memory>
#include <map>
#include "EntityComponentDef.h"
class EntityComponentFactory
{
public:
	EntityComponentFactory(void);
	~EntityComponentFactory(void);

	static EntityComponentFactory& getInstance();

	static std::unique_ptr<EntityComponent> makeComponent(EntityComponentID::E componentID);
	static std::unique_ptr<EntityComponent> makeComponent(const std::string& componentStr);

	static EntityComponentID::E stringToID(const std::string& str);
	static std::string IDToString(EntityComponentID::E id);

private:
	std::unordered_map<EntityComponentID::E, std::string> m_strMap;
	std::unordered_map<std::string, EntityComponentID::E> m_idMap;
};

