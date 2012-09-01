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

	EntityComponentID getType() {return type;}

private:
	const EntityComponentID type;
};

