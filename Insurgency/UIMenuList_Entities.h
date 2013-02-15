#pragma once
#include "UIMenuList.h"
#include "InventoryComponent.h"
#include "EquipSlotsComponent.h"
class UIMenuList_Entities :
	public UIMenuList
{
public:
	UIMenuList_Entities(void);
	UIMenuList_Entities(InventoryComponent& inventory, GameEntity& actor);
	UIMenuList_Entities(EquipSlotsComponent& equipSlots, GameEntity& actor);
	~UIMenuList_Entities(void);

	void addEntity(GameEntity& entity);
	void removeEntity(int index);
	int getEntitySelection(const GameEntity& entity);

private:
	std::vector<GameEntity*> m_entities;
	GameEntity* m_actor;


	friend class UIMenu_Creature;
};

