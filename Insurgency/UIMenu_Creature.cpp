#include "StdAfx.h"
#include "UIMenu_Creature.h"


UIMenu_Creature::UIMenu_Creature(void)
	:UIMenu(),
	m_trunk(),
	m_inventoryMenuList(),
	m_inventoryMenuOption("Inventory", &m_inventoryMenuList)
{
	m_inventoryMenuOption.m_helpText = "Items in the creature's backpack";

	m_trunk.m_options.push_back(&m_inventoryMenuOption);

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

void UIMenu_Creature::executeSelection()
{
	UIMenuOption* option = m_currentMenuList->m_options[m_selection];
}