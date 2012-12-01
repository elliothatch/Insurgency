#include "StdAfx.h"
#include "UIMenu_Creature.h"


UIMenu_Creature::UIMenu_Creature(void)
	:UIMenu(),
	m_inventoryMenuList(),
	m_inventoryMenuOption("Inventory", &m_inventoryMenuList)
{
	UIMenuList trunk;
	
	m_inventoryMenuOption.m_helpText = "Items in the creature's backpack";

	trunk.m_options.push_back(&m_inventoryMenuOption);

	setTrunk(&trunk);
	//m_helpText = currentMenuList
}


UIMenu_Creature::~UIMenu_Creature(void)
{
}
