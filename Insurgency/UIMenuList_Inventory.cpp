#include "StdAfx.h"
#include "UIMenuList_Inventory.h"


UIMenuList_Inventory::UIMenuList_Inventory(void)
	:m_inventory()
{
}

UIMenuList_Inventory::UIMenuList_Inventory(InventoryComponent& inventory)
	:m_inventory(&inventory)
{
	std::vector<GameEntity*> entities = m_inventory->getItemList();
	for(std::vector<GameEntity*>::iterator entityIt(entities.begin()); entityIt != entities.end(); entityIt++)
	{
		addEntity(*entityIt);
	}
}

UIMenuList_Inventory::~UIMenuList_Inventory(void)
{
}

void UIMenuList_Inventory::addEntity(GameEntity* entity)
{
	UIMenuList usageOptions;
	std::set<EntityActionID::E> actions = m_inventory->getEntity()->getPerformableActions(entity);
	for(std::set<EntityActionID::E>::iterator actionIt(actions.begin()); actionIt != actions.end(); actionIt++)
	{
		usageOptions.m_options.push_back(UIMenuOption_EntityActionDef::getMenuOption(*actionIt));
	}
}