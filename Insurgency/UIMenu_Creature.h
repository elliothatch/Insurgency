#pragma once
#include "UIMenu.h"
#include "UIMenuList_Entities.h"
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
	UIMenuList_Entities m_inventoryMenuList;
	UIMenuOption m_inventoryMenuOption;
	UIMenuList_Entities m_equipMenuList;
	UIMenuOption m_equipMenuOption;
	GameTurnTimer* m_gameTurnTimer;
	Creature* m_creature;
};

