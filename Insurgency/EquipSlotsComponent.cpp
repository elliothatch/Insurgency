#include "StdAfx.h"
#include "EquipSlotsComponent.h"

EquipSlotsComponent::EquipSlotsComponent(void)
	:EntityComponent(EntityComponentID::EquipSlots),
	 m_equippedEntities(),
	 m_equipSlots()
{
}


EquipSlotsComponent::~EquipSlotsComponent(void)
{
}

EquipSlotsComponent* EquipSlotsComponent::clone() const
{
	return new EquipSlotsComponent(*this);
}

void EquipSlotsComponent::equipEntity(GameEntity& target, const GameEntityEquipGroups::EquipGroup& equipGroup)
{
	m_equippedEntities[&target] = equipGroup;
	for(auto slotIt(equipGroup.m_equipSlots.begin()); slotIt != equipGroup.m_equipSlots.end(); slotIt++)
	{
		auto equipIt = m_equipSlots.find(*slotIt);
		if(equipIt != m_equipSlots.end())
		{
			equipIt->second = &target;
		}
	}
}

void EquipSlotsComponent::unequipEntity(GameEntity& target)
{
	auto entityIt = m_equippedEntities.find(&target);
	if(entityIt != m_equippedEntities.end())
	{
		for(auto slotIt(entityIt->second.m_equipSlots.begin()); slotIt != entityIt->second.m_equipSlots.end(); slotIt++)
		{
			auto equipIt = m_equipSlots.find(*slotIt);
			if(equipIt != m_equipSlots.end())
			{
				equipIt->second = nullptr;
			}
		}
		m_equippedEntities.erase(entityIt);
	}
}

std::map<GameEntity*,GameEntityEquipGroups::EquipGroup> EquipSlotsComponent::getEquippedEntities() const
{
	return m_equippedEntities;
}

bool EquipSlotsComponent::isEntityEquipped(GameEntity& target) const
{
	return (m_equippedEntities.find(&target) != m_equippedEntities.end());
}

void EquipSlotsComponent::addEquipSlot(EntityEquipSlotID::E slot)
{
	m_equipSlots.insert(std::pair<EntityEquipSlotID::E,GameEntity*>(slot,nullptr));
}

bool EquipSlotsComponent::hasEquipSlot(EntityEquipSlotID::E slot) const
{
	return (m_equipSlots.find(slot) != m_equipSlots.end());
}

bool EquipSlotsComponent::hasEquipSlots(const GameEntityEquipGroups::EquipGroup& equipGroup) const
{
	for(auto slotIt(equipGroup.m_equipSlots.begin()); slotIt != equipGroup.m_equipSlots.end(); slotIt++)
	{
		if(m_equipSlots.find(*slotIt) == m_equipSlots.end())
		{
			return false;
		}
	}
	return true;
}

std::map<EntityEquipSlotID::E,GameEntity*> EquipSlotsComponent::getEquipSlots() const
{
	return m_equipSlots;
}

GameEntity* EquipSlotsComponent::getEntityEquippedInSlot(EntityEquipSlotID::E slot) const
{
	auto slotIt = m_equipSlots.find(slot);
	if(slotIt != m_equipSlots.end())
	{
		return slotIt->second;
	}
	return nullptr; //return nullptr if there is no such slot
}