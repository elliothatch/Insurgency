#pragma once
#include "EntityComponent.h"
class EquipSlotComponent : public EntityComponent
{
public:
	EquipSlotComponent(void);
	virtual ~EquipSlotComponent(void);

	void equipEntity(GameEntity* target);
	GameEntity* getEquippedEntity() const;



private:
	GameEntity* m_equippedEntity;
};

