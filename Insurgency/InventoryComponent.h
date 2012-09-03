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
	void addEntity(GameEntity* lEntity);
	void removeEntity(GameEntity* lEntity);

private:
	std::vector<GameEntity*> storage;
};

