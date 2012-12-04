#pragma once
#include "UIMenuList.h"
#include "InventoryComponent.h"
#include "UIMenuOption_EntityActionDef.h"
class UIMenuList_Inventory :
	public UIMenuList
{
public:
	UIMenuList_Inventory(void);
	UIMenuList_Inventory(InventoryComponent& inventory);
	~UIMenuList_Inventory(void);

	void addEntity(GameEntity* entity);

private:
	std::vector<std::pair<std::unique_ptr<UIMenuList>, std::unique_ptr<UIMenuOption>>> m_entities;
	InventoryComponent* m_inventory;


	friend class UIMenu_Creature;
};

