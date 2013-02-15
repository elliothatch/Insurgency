#include "StdAfx.h"
#include "UIMenuList_Entities.h"


UIMenuList_Entities::UIMenuList_Entities(void)
	:m_entities(),
	 m_actor(nullptr)
{
}

UIMenuList_Entities::UIMenuList_Entities(InventoryComponent& inventory, GameEntity& actor)
	:m_entities(),
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
	:m_entities(),
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
	std::set<EntityActionID::E> actions = m_actor->getPerformableActions(entity);
	for(std::set<EntityActionID::E>::iterator actionIt(actions.begin()); actionIt != actions.end(); actionIt++)
	{
		std::unique_ptr<UIMenuOption> actionOption(new UIMenuOption(GameEntityActions::getActionName(*actionIt)));
		actionOption->m_selectionStep = GameEntityActions::getActionSelectionStep(*actionIt);
		actionOption->m_tag = actionOption->m_name;
		std::unique_ptr<UIMenuList> subActionList(nullptr);

		//push equip groups
		if(actionOption->m_tag == GameEntityActions::getActionName(EntityActionID::Equip))
		{
			subActionList.reset(new UIMenuList());
			auto& equipGroups = entity.getGameEntityEquipGroups().getEquipGroups();
			for(auto entityIt = equipGroups.begin(); entityIt != equipGroups.end(); entityIt++)
			{
				std::unique_ptr<UIMenuOption> equipGroupOption(new UIMenuOption(entityIt->getName(),nullptr,"GameEntityEquipGroup"));
				equipGroupOption->m_selectionStep = GameEntityActions::getActionSelectionStep(EntityActionID::Equip);
				subActionList->pushNewMenuOption(std::unique_ptr<UIMenuList>(nullptr), std::move(equipGroupOption));
			}
		}
		actionOption->m_target = subActionList.get();
		actionList->pushNewMenuOption(std::move(subActionList), std::move(actionOption));
		//pushNewMenuOption(std::move(actionList),std::move(listOption));
	}
	if(actionList->m_options.size() == 0)
		actionList->m_accessible = false;
	pushNewMenuOption(std::move(actionList), std::move(listOption));
	m_accessible = true;
}

void UIMenuList_Entities::removeEntity(int index)
{
	m_entities.erase(m_entities.begin() + index);
	eraseMenuOption(index);
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