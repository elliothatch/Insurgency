#pragma once
#include "EntityComponent.h"
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

	void equipEntity(GameEntity& target);
	void unequipEntity(GameEntity& target);
	GameEntity* getEquippedEntity() const;
	bool isEntityEquipped(GameEntity& target) const;

	void addEquipSlot(SlotID::E slot);
	std::set<SlotID::E> getEquipSlots() const;


private:
	GameEntity* m_equippedEntity;
	std::set<SlotID::E> m_equipSlots;
};

