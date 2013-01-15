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

	if(option == UIMenuOption_EntityActionDef::getMenuOption(EntityActionID::Drop))
	{
		UIMenuList_Entities* entityMenuList = dynamic_cast<UIMenuList_Entities*>(m_previousMenuList);
		if(m_gameTurnTimer->creatureDropItem(*m_creature, 
			*dynamic_cast<GameItem*>(entityMenuList->m_entities.at(m_previousMenuList->m_selection))))
		{
			entityMenuList->removeEntityMenuOption(m_previousMenuList->m_options[m_previousMenuList->m_selection]);
		}
	}
	else if(option == UIMenuOption_EntityActionDef::getMenuOption(EntityActionID::Equip))
	{
		GameEntity* entity = m_inventoryMenuList.m_entities.at(m_inventoryMenuList.m_selection);
		GameEntity* oldEntity = nullptr;
		const GameEntityEquipGroups::EquipGroup& equipGroup = *entity->getGameEntityEquipGroups().getEquipGroups().begin();
		for(auto slotIt(equipGroup.m_equipSlots.begin()); slotIt != equipGroup.m_equipSlots.end(); slotIt++)
		{
			if(oldEntity = m_creature->getEquipSlotsComponent()->getEntityEquippedInSlot(*slotIt))
				break;
		}
		if(m_gameTurnTimer->creatureEquipItem(*m_creature,*dynamic_cast<GameItem*>(entity),equipGroup))
		{
			m_inventoryMenuList.removeEntityMenuOption(m_previousMenuList->m_options[m_previousMenuList->m_selection]);
			if(oldEntity)
			{
				m_equipMenuList.removeEntityMenuOption(m_equipMenuList.m_options[m_equipMenuList.m_selection]);
				m_inventoryMenuList.addEntity(oldEntity);
			}
			m_equipMenuList.addEntity(entity);
		}
		else
		{
			return 1;
		}
	}
	else if(option == UIMenuOption_EntityActionDef::getMenuOption(EntityActionID::Unequip))
	{
		GameEntity* entity = m_equipMenuList.m_entities.at(m_equipMenuList.m_selection);
		if(m_gameTurnTimer->creatureUnequipItem(*m_creature,
			*dynamic_cast<GameItem*>(entity)))
		{
			if(m_creature->getInventoryComponent()->isEntityContained(*entity))
				m_inventoryMenuList.addEntity(entity);
			m_equipMenuList.removeEntityMenuOption(m_previousMenuList->m_options[m_previousMenuList->m_selection]);
		}
		else
		{
			return 1;
		}
	}
	return option->m_selectionStep;
}