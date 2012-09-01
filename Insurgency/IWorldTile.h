#pragma once
#include "WorldTileType.h"
#include <string>
//IGameRegion is constructed of IWorldTiles
//IWorldTiles get their properties from WorldTileType
class IWorldTile
{
public:

	IWorldTile(const WorldTileType& lType)
	{
	}

	virtual ~IWorldTile(void)
	{
	}

	virtual bool isPassable(void) = 0;
	virtual bool isTransparent(void) = 0;
	virtual std::string getTitle(void) = 0;

	//temp test
	virtual char getDispCh(void) = 0;
};

