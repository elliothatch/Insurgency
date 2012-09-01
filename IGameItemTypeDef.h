#pragma once
#include "GameItemType.h"
class IGameItemTypeDef
{
public:

	IGameItemTypeDef(void)
	{
	}

	virtual ~IGameItemTypeDef(void)
	{
	}

	virtual const GameItemType& getTileType(GameItemTypeID lTypeID) const = 0;
	//virtual void registerItemype(GameItemType lItemType) = 0;
};

