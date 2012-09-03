#pragma once
#include "EntityComponentEnum.h"
class EntityComponent
{
public:

	EntityComponent(EntityComponentID lType)
		:type(lType)
	{
	}

	virtual ~EntityComponent(void)
	{
	}

	virtual EntityComponent* clone() const = 0;

	EntityComponentID getType() {return type;}

private:
	const EntityComponentID type;
};

