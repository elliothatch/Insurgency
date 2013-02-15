#pragma once

class GameEntity;
struct EntityComponentID
{
	enum E
	{
		Inventory,
		EquipSlots,
		RangedWeapon,
		Count
	};
};

class EntityComponent
{
public:

	EntityComponent(EntityComponentID::E lType);

	virtual ~EntityComponent(void);
	virtual EntityComponent* clone() const = 0;

	void setEntity(GameEntity& lEntity);

	EntityComponentID::E getType();
	GameEntity* getEntity();

private:
	EntityComponentID::E m_type; //const
	GameEntity* m_entity;
};

