#include "StdAfx.h"
#include "UIMenuList_Entities.h"


UIMenuList_Entities::UIMenuList_Entities(void)
	:m_entityOptions(),
	 m_entities(),
	 m_actor(nullptr)
{
}

UIMenuList_Entities::UIMenuList_Entities(InventoryComponent& inventory, GameEntity& actor)
	:m_entityOptions(),
	 m_entities(),
	 m_actor(&actor)
{
	m_accessible = false;
	std::vector<GameEntity*> entities = inventory.getItemList();
	for(std::vector<GameEntity*>::iterator entityIt(entities.begin()); entityIt != entities.end(); entityIt++)
	{
		addEntity(**entityIt);
	}
}

UIMenuList_Entities::UIMenuList_Entities(EquipSlotsComponent& equipSlots, GameEntity& actor)
	:m_entityOptions(),
	 m_entities(),
	 m_actor(&actor)
{
	m_accessible = false;
	auto entities = equipSlots.getEquippedEntities();
	for(auto entityIt(entities.begin()); entityIt != entities.end(); entityIt++)
	{
		addEntity(*entityIt->first);
	}
}

UIMenuList_Entities::~UIMenuList_Entities(void)
{
}

void UIMenuList_Entities::addEntity(GameEntity& entity)
{
	m_entities.push_back(&entity);
	std::unique_ptr<UIMenuList> actionList(new UIMenuList());
	std::unique_ptr<UIMenuOption> listOption(new UIMenuOption(entity.getSName(), actionList.get()));
	std::set<EntityActionID::E> actions = m_actor->getPerformableActions(&entity);
	for(std::set<EntityActionID::E>::iterator actionIt(actions.begin()); actionIt != actions.end(); actionIt++)
	{
		actionList->m_options.push_back(UIMenuOption_EntityActionDef::getMenuOption(*actionIt));
	}
	if(actionList->m_options.size() == 0)
		actionList->m_accessible = false;
	m_options.push_back(listOption.get());
	m_entityOptions.push_back(std::make_pair<std::unique_ptr<UIMenuList>,std::unique_ptr<UIMenuOption>>(
		std::move(actionList),std::move(listOption)));
	m_accessible = true;
}

void UIMenuList_Entities::removeEntityMenuOption(UIMenuOption* menuOption)
{
	std::vector<UIMenuOption*>::iterator optionIt = std::find(m_options.begin(), m_options.end(), menuOption);
	int optionIndex = optionIt - m_options.begin();
	m_options.erase(optionIt);
	m_entities.erase(m_entities.begin() + optionIndex);
	m_entityOptions.erase(m_entityOptions.begin() + optionIndex);
	if(m_selection >= static_cast<int>(m_options.size()) && m_selection != 0)
		m_selection = m_options.size()-1;
	if(m_options.size() == 0)
		m_accessible = false;
}

int UIMenuList_Entities::getEntitySelection(const GameEntity& entity)
{
	auto entityIt(std::find_if(m_entities.begin(),m_entities.end(),
		[&](GameEntity* mEntity){return mEntity == &entity;}));
	if(entityIt != m_entities.end())
	{
		return (entityIt - m_entities.begin());
	}
	return -1;
}