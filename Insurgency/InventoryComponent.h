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

	int getNumEntities() const;
	std::vector<GameEntity*> getItemList() const;

	bool isEntityContained(GameEntity& lEntity) const;

	bool canAddEntity(GameEntity& lEntity) const;

private:
	std::vector<GameEntity*> m_storage;
};