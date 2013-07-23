#include "StdAfx.h"
#include "EntityComponentFactory.h"

#include <array>
#include <iostream>
EntityComponentFactory* s_EntityComponentFactory = nullptr;

EntityComponentFactory::EntityComponentFactory(void)
	:m_strMap(),
	 m_idMap()
{
	for(auto nameIt(s_componentNames.begin()); nameIt != s_componentNames.end(); nameIt++)
	{
		m_strMap.insert(*nameIt);
		m_idMap.insert(std::make_pair(nameIt->second, nameIt->first));
	}
}


EntityComponentFactory::~EntityComponentFactory(void)
{
}

EntityComponentFactory& EntityComponentFactory::getInstance()
{
	if(s_EntityComponentFactory == nullptr)
	{
		s_EntityComponentFactory = new EntityComponentFactory();
	}
	return *s_EntityComponentFactory;
}

std::unique_ptr<EntityComponent> EntityComponentFactory::makeComponent(EntityComponentID::E componentID)
{
	std::unique_ptr<EntityComponent> component;
	switch(componentID)
	{
	case EntityComponentID::Inventory:
		component.reset(new InventoryComponent());
		break;
	case EntityComponentID::EquipSlots:
		component.reset(new EquipSlotsComponent());
		break;
	case EntityComponentID::RangedWeapon:
		component.reset(new RangedWeaponComponent());
		break;
	default:
		printf("ERROR: Entity Component Factory Invalid ComponentID: %d\n", componentID);
	}
	return component;
}

std::unique_ptr<EntityComponent> EntityComponentFactory::makeComponent(const std::string& componentStr)
{
	return makeComponent(stringToID(componentStr));
}

EntityComponentID::E EntityComponentFactory::stringToID(const std::string& str)
{
	return getInstance().m_idMap.find(str)->second;
}

std::string EntityComponentFactory::IDToString(EntityComponentID::E id)
{
	return getInstance().m_strMap.find(id)->second;
}