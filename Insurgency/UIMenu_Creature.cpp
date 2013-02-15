#include "StdAfx.h"
#include "UIMenu_Creature.h"


UIMenu_Creature::UIMenu_Creature(GameTurnTimer& gameTurnTimer, Creature& creature)
	:UIMenu(),
	m_trunk(),
	m_inventoryMenuList(*creature.getInventoryComponent(), creature),
	m_inventoryMenuOption("Inventory", &m_inventoryMenuList),
	m_equipMenuList(*creature.getEquipSlotsComponent(), creature),
	m_equipMenuOption("Equipment", &m_equipMenuList),
	m_gameTurnTimer(&gameTurnTimer),
	m_creature(&creature)
{
	m_inventoryMenuOption.m_helpText = "Items in the creature's backpack";
	m_equipMenuOption.m_helpText = "Items the creature has equipped";

	m_trunk.m_options.push_back(&m_inventoryMenuOption);
	m_trunk.m_options.push_back(&m_equipMenuOption);

	setTrunk(&m_trunk);
	//m_helpText = currentMenuList
}


UIMenu_Creature::~UIMenu_Creature(void)
{
}

void UIMenu_Creature::changeSelection()
{
	if(m_currentMenuList->m_options.size() == 0)
		return;

	UIMenuOption* option = m_currentMenuList->m_options[m_selection];
	m_helpText = option->m_helpText;
}

int UIMenu_Creature::executeSelection()
{
	UIMenuOption* option = m_currentMenuList->m_options[m_selection];
	int selectionStep = option->m_selectionStep;

	if(option->m_tag == GameEntityActions::getActionName(EntityActionID::Drop))
	{
		UIMenuList_Entities* entityMenuList = dynamic_cast<UIMenuList_Entities*>(m_previousMenuList);
		if(m_gameTurnTimer->creatureDropItem(*m_creature, 
			*dynamic_cast<GameItem*>(entityMenuList->m_entities.at(m_previousMenuList->m_selection))))
		{
			entityMenuList->removeEntity(m_previousMenuList->m_selection);
		}
	}
	else if(option->m_tag == "GameEntityEquipGroup")
	{
		if(m_previousMenuList->m_options[m_previousMenuList->m_selection]->m_tag == GameEntityActions::getActionName(EntityActionID::Equip))
		{
			GameEntity* entity = m_inventoryMenuList.m_entities.at(m_inventoryMenuList.m_selection);
			std::set<GameEntity*> oldEntities;
			const GameEntityEquipGroups::EquipGroup& equipGroup = entity->getGameEntityEquipGroups().getEquipGroups().at(m_selection);
			for(auto slotIt(equipGroup.m_equipSlots.begin()); slotIt != equipGroup.m_equipSlots.end(); slotIt++)
			{
				if(GameEntity* oldEntity = m_creature->getEquipSlotsComponent()->getEntityEquippedInSlot(*slotIt))
					oldEntities.insert(oldEntity);
			}
			if(m_gameTurnTimer->creatureEquipItem(*m_creature,*dynamic_cast<GameItem*>(entity),equipGroup))
			{
				m_inventoryMenuList.removeEntity(m_branch.at(m_branch.size()-3)->m_selection);
				for(auto oldEntityIt(oldEntities.begin()); oldEntityIt != oldEntities.end(); oldEntityIt++)
				{
					int entityIndex = m_equipMenuList.getEntitySelection(**oldEntityIt);
					//if(entityIndex != -1) should always succeed.
					m_equipMenuList.removeEntity(entityIndex);
					m_inventoryMenuList.addEntity(**oldEntityIt);
				}
				m_equipMenuList.addEntity(*entity);
			}
			else
			{
				return 1;
			}
		}
	}
	else if(option->m_tag == GameEntityActions::getActionName(EntityActionID::Unequip))
	{
		GameEntity* entity = m_equipMenuList.m_entities.at(m_equipMenuList.m_selection);
		if(m_gameTurnTimer->creatureUnequipItem(*m_creature, *dynamic_cast<GameItem*>(entity)))
		{
			if(m_creature->getInventoryComponent()->isEntityContained(*entity))
				m_inventoryMenuList.addEntity(*entity);
			m_equipMenuList.removeEntity(m_previousMenuList->m_selection);
		}
		else
		{
			return 1;
		}
	}
	return selectionStep;
}