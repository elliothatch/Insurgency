#pragma once

struct EntityComponentID
{
	enum E
	{
		Inventory,
		Gun,
		Count
	};
};

class EntityComponent
{
public:

	EntityComponent(EntityComponentID::E lType);

	virtual ~EntityComponent(void);
	virtual EntityComponent* clone() const = 0;

	EntityComponentID::E getType();

private:
	const EntityComponentID::E m_type;
};

