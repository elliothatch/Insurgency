#include "StdAfx.h"
#include "InventoryComponent.h"


InventoryComponent::InventoryComponent(void)
	:EntityComponent(INVENTORY)
{
}


InventoryComponent::~InventoryComponent(void)
{
}

void InventoryComponent::addEntity(GameEntity* lEntity)
{
	storage.push_back(lEntity);
}

void InventoryComponent::removeEntity(GameEntity* lEntity)
{
	std::vector<GameEntity*>::iterator storageIt = std::find(storage.begin(), storage.end(), lEntity);
	//if the item is found in the inventory
	if(storageIt != storage.end())
	{
		storage.erase(storageIt);
	}
}