#pragma once
#include "CreatureType.h"
#include "InventoryComponent.h"
class ICreatureTypeDef
{
public:

	ICreatureTypeDef(void)
	{
	}

	virtual ~ICreatureTypeDef(void)
	{
	}

	virtual const CreatureType& getCreatureType(CreatureTypeID lTypeID) const = 0;
	//virtual void registerCreatureType(CreatureType lType) = 0;
};

