#pragma once

#include "WorldTileType.h"
typedef unsigned int WorldTileTypeID;

class IWorldTileTypeDef
{
public:

	IWorldTileTypeDef(void)
	{
	}

	virtual ~IWorldTileTypeDef(void)
	{
	}

	virtual const WorldTileType& getTileType(WorldTileTypeID lID) const = 0;
	//virtual void registerTileType(WorldTileType lTileType) = 0;

};

