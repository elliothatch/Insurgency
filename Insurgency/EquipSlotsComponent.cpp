#include "StdAfx.h"
#include "EquipSlotsComponent.h"

EquipSlotsComponent::EquipSlotsComponent(void)
	:EntityComponent(EntityComponentID::EquipSlots),
	 m_equippedEntity(nullptr)
{
}


EquipSlotsComponent::~EquipSlotsComponent(void)
{
}

void EquipSlotsComponent::equipEntity(GameEntity& target)
{
	m_equippedEntity = &target;
}

void EquipSlotsComponent::unequipEntity(GameEntity& target)
{
	if(&target == m_equippedEntity)
	{
		m_equippedEntity = false;
	}
}

GameEntity* EquipSlotsComponent::getEquippedEntity() const
{
	return m_equippedEntity;
}

bool EquipSlotsComponent::isEntityEquipped(GameEntity& target) const
{
	return (&target == m_equippedEntity);
}