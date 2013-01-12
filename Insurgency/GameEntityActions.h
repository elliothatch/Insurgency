#pragma once
#include <set>
struct EntityActionID
{
	enum E
	{
		PickUp,
		Drop,
		Equip,
		Unequip,
		Count
	};
};

class GameEntityActions
{
public:
	GameEntityActions();
	GameEntityActions(std::set<EntityActionID::E> inventoryActions, std::set<EntityActionID::E> equippedActions, 
		std::set<EntityActionID::E> worldActions);
	~GameEntityActions();
	void setInventoryActions(std::set<EntityActionID::E> actions);
	void setEquippedActions(std::set<EntityActionID::E> actions);
	void setWorldActions(std::set<EntityActionID::E> actions);

	void addInventoryAction(EntityActionID::E action);
	void addEquippedAction(EntityActionID::E action);
	void addWorldAction(EntityActionID::E action);

	std::set<EntityActionID::E> getInventoryActions() const;
	std::set<EntityActionID::E> getEquippedActions() const;
	std::set<EntityActionID::E> getWorldActions() const;

private:
	std::set<EntityActionID::E> m_actionsInv;
	std::set<EntityActionID::E> m_actionsEquip;
	std::set<EntityActionID::E> m_actionsWorld;
};