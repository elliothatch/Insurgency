#pragma once
#include "UIMenu.h"
#include "UIMenuList_Inventory.h"
class UIMenu_Creature :
	public UIMenu
{
public:
	UIMenu_Creature(void);
	~UIMenu_Creature(void);
private:
	UIMenuList_Inventory m_inventoryMenuList;
	UIMenuOption m_inventoryMenuOption;
};

