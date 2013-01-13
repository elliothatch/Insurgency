#pragma once
#include "EntityComponent.h"
#include <set>
#include <map>
class EquipSlotsComponent : public EntityComponent
{
public:
	struct SlotID
	{
		enum E
		{
			heldRight = 0, //held in your hand
			heldLeft,
			handRight,     //gloves, etc.
			handLeft,
			forearmRight,
			forearmLeft,
			shoulderRight,
			shoulderLeft,
			neck,
			head,
			eyes,	//goggles/blindfold
			chest,
			abdomen,
			groin,
			thighRight,
			thighLeft,
			shinRight,
			shinLeft,
			footRight,
			footLeft,
			count
		};
	};

	EquipSlotsComponent(void);
	virtual ~EquipSlotsComponent(void);

	virtual EquipSlotsComponent* clone() const;

	void equipEntity(GameEntity& target, std::set<SlotID::E> slots);
	void unequipEntity(GameEntity& target);
	std::map<GameEntity*,std::set<SlotID::E>> getEquippedEntities() const;
	bool isEntityEquipped(GameEntity& target) const;

	void addEquipSlot(SlotID::E slot);
	bool hasEquipSlot(SlotID::E slot);
	bool hasEquipSlots(std::set<SlotID::E> slots);
	std::map<SlotID::E,GameEntity*> getEquipSlots() const;
	GameEntity* getEntityEquippedInSlot(SlotID::E slot) const;


private:
	std::map<GameEntity*,std::set<SlotID::E>> m_equippedEntities;
	std::map<SlotID::E,GameEntity*> m_equipSlots;
};

