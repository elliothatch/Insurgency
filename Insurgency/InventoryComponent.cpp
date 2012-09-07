#include "StdAfx.h"
#include "InventoryComponent.h"


InventoryComponent::InventoryComponent(void)
	:EntityComponent(EntityComponentID::Inventory)
{
}


InventoryComponent::~InventoryComponent(void)
{
}

InventoryComponent* InventoryComponent::clone() const
{
	return new InventoryComponent(*this);
}

void InventoryComponent::addEntity(GameEntity& lEntity)
{
	m_storage.push_back(&lEntity);
}

void InventoryComponent::removeEntity(GameEntity& lEntity)
{
	std::vector<GameEntity*>::iterator storageIt = std::find(m_storage.begin(), m_storage.end(), &lEntity);
	//if the item is found in the inventory
	if(storageIt != m_storage.end())
	{
		m_storage.erase(storageIt);
	}
}

GameEntity& InventoryComponent::getEntityAtIndex(int index) const
{
	return *m_storage.at(index);
}

void InventoryComponent::removeEntityAtIndex(int index)
{
	m_storage.erase(m_storage.begin() + index);
}

int InventoryComponent::getNumItems() const
{
	return m_storage.size();
}

std::vector<GameEntity*> InventoryComponent::getItemList() const
{
	return m_storage;
}