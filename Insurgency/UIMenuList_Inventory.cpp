#include "StdAfx.h"
#include "UIMenuList_Inventory.h"


UIMenuList_Inventory::UIMenuList_Inventory(void)
	:m_inventory()
{
}

UIMenuList_Inventory::UIMenuList_Inventory(InventoryComponent& inventory)
	:m_inventory(&inventory)
{
	m_accessible = false;
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
	std::unique_ptr<UIMenuList> actionList(new UIMenuList());
	std::unique_ptr<UIMenuOption> listOption(new UIMenuOption(entity->getSName(), actionList.get()));
	std::set<EntityActionID::E> actions = m_inventory->getEntity()->getPerformableActions(entity);
	for(std::set<EntityActionID::E>::iterator actionIt(actions.begin()); actionIt != actions.end(); actionIt++)
	{
		actionList->m_options.push_back(UIMenuOption_EntityActionDef::getMenuOption(*actionIt));
	}
	if(actionList->m_options.size() == 0)
		actionList->m_accessible = false;
	m_options.push_back(listOption.get());
	m_entities.push_back(std::make_pair<std::unique_ptr<UIMenuList>,std::unique_ptr<UIMenuOption>>(
		std::move(actionList),std::move(listOption)));
	m_accessible = true;
}

void UIMenuList_Inventory::removeEntityMenuOption(UIMenuOption* menuOption)
{

	std::vector<UIMenuOption*>::iterator optionIt = std::find(m_options.begin(), m_options.end(), menuOption);
	m_entities.erase(m_entities.begin() + (optionIt - m_options.begin()));
	m_options.erase(optionIt);
	if(m_selection >= static_cast<int>(m_options.size()))
		m_selection = m_options.size()-1;
	if(m_options.size() == 0)
		m_accessible = false;
}