#pragma once
#include "UIMenuList.h"
#include "InventoryComponent.h"
#include "EquipSlotsComponent.h"
#include "UIMenuOption_EntityActionDef.h"
class UIMenuList_Entities :
	public UIMenuList
{
public:
	UIMenuList_Entities(void);
	UIMenuList_Entities(InventoryComponent& inventory, GameEntity& actor);
	UIMenuList_Entities(EquipSlotsComponent& equipSlots, GameEntity& actor);
	~UIMenuList_Entities(void);

	void addEntity(GameEntity* entity);
	void removeEntityMenuOption(UIMenuOption* menuOption);

private:
	std::vector<std::pair<std::unique_ptr<UIMenuList>, std::unique_ptr<UIMenuOption>>> m_entityOptions;
	std::vector<GameEntity*> m_entities;
	GameEntity* m_actor;


	friend class UIMenu_Creature;
};

