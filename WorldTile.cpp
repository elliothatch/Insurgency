#include "StdAfx.h"
#include "WorldTile.h"


WorldTile::WorldTile(const WorldTileType& lType)
	:IWorldTile(lType),
	type(lType)
{
}


WorldTile::~WorldTile(void)
{
}
