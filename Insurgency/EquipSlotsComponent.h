#pragma once
#include "EntityComponent.h"
#include <set>
#include <map>
#include "GameEntityEquipGroups.h"
class EquipSlotsComponent : public EntityComponent
{
public:

	EquipSlotsComponent(void);
	virtual ~EquipSlotsComponent(void);

	virtual EquipSlotsComponent* clone() const;

	void equipEntity(GameEntity& target, const GameEntityEquipGroups::EquipGroup& equipGroup);
	void unequipEntity(GameEntity& target);
	std::map<GameEntity*,GameEntityEquipGroups::EquipGroup> getEquippedEntities() const;
	bool isEntityEquipped(GameEntity& target) const;

	void addEquipSlot(EntityEquipSlotID::E slot);
	bool hasEquipSlot(EntityEquipSlotID::E slot) const;
	bool hasEquipSlots(const GameEntityEquipGroups::EquipGroup& equipGroup) const;
	std::map<EntityEquipSlotID::E,GameEntity*> getEquipSlots() const;
	GameEntity* getEntityEquippedInSlot(EntityEquipSlotID::E slot) const;


private:
	std::map<GameEntity*,GameEntityEquipGroups::EquipGroup> m_equippedEntities;
	std::map<EntityEquipSlotID::E,GameEntity*> m_equipSlots;
};

