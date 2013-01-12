#pragma once
#include "EntityComponent.h"
class EquipSlotsComponent : public EntityComponent
{
public:
	EquipSlotsComponent(void);
	virtual ~EquipSlotsComponent(void);

	virtual EquipSlotsComponent* clone() const;

	void equipEntity(GameEntity& target);
	void unequipEntity(GameEntity& target);
	GameEntity* getEquippedEntity() const;
	bool isEntityEquipped(GameEntity& target) const;


private:
	GameEntity* m_equippedEntity;
};

