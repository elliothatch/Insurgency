#pragma once
#include "entitycomponent.h"
#include "GameEntity.h"
#include <algorithm>
#include <vector>
class InventoryComponent :
	public EntityComponent
{
public:
	InventoryComponent(void);
	virtual ~InventoryComponent(void);
	virtual InventoryComponent* clone() const;

	void addEntity(GameEntity& lEntity);
	void removeEntity(GameEntity& lEntity);

	GameEntity& getEntityAtIndex(int index) const;
	void removeEntityAtIndex(int index);

	int getNumItems() const;
	std::vector<GameEntity*> getItemList() const;

private:
	std::vector<GameEntity*> m_storage;
};