#include "StdAfx.h"
#include "EquipSlotComponent.h"
#include "GameEntity.h"

EquipSlotComponent::EquipSlotComponent(void)
	:EntityComponent(EntityComponentID::EquipSlot),
	 m_equippedEntity(nullptr)
{
}


EquipSlotComponent::~EquipSlotComponent(void)
{
}

void EquipSlotComponent::equipEntity(GameEntity* target)
{
	if(GameEntity* holdingEntity = getEntity())
	{
		if(holdingEntity->canEquipEntity(target))
		{
			if(m_equippedEntity)
			{
				//drop old entity
			}
			m_equippedEntity = target;
		}
	}
}

GameEntity* EquipSlotComponent::getEquippedEntity() const
{
	return m_equippedEntity;
}
