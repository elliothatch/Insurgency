#pragma once
#include "EntityComponentEnum.h"
class EntityComponent
{
public:

	EntityComponent(EntityComponentID lType);

	virtual ~EntityComponent(void);
	virtual EntityComponent* clone() const = 0;

	EntityComponentID getType();

private:
	const EntityComponentID m_type;
};

