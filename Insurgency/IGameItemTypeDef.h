#pragma once
#include "GameItemType.h"
#include "EntityComponentIncludes.h"
class IGameItemTypeDef
{
public:

	IGameItemTypeDef(void)
	{
	}

	virtual ~IGameItemTypeDef(void)
	{
	}

	virtual const GameItemType& getItemType(GameItemTypeID lTypeID) const = 0;
	//virtual void registerItemype(GameItemType lItemType) = 0;
};

