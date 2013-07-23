#pragma once

#include <array>
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
const std::array<std::pair<const EntityComponentID::E,const std::string>, EntityComponentID::Count> s_componentNames =
{
	std::make_pair(EntityComponentID::Inventory, "Inventory"),
	std::make_pair(EntityComponentID::EquipSlots, "EquipSlots"),
	std::make_pair(EntityComponentID::RangedWeapon, "RangedWeapon")
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

