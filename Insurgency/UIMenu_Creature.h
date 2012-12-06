#pragma once
#include "UIMenu.h"
#include "UIMenuList_Inventory.h"
#include "GameTurnTimer.h"
class UIMenu_Creature :
	public UIMenu
{
public:
	UIMenu_Creature(GameTurnTimer& gameTurnTimer, Creature& creature);
	~UIMenu_Creature(void);

	virtual void changeSelection();
	virtual int executeSelection();

private:
	UIMenuList m_trunk;
	UIMenuList_Inventory m_inventoryMenuList;
	UIMenuOption m_inventoryMenuOption;
	GameTurnTimer* m_gameTurnTimer;
	Creature* m_creature;
};

