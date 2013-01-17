#include "StdAfx.h"
#include "WorldTile.h"


WorldTile::WorldTile(const WorldTileType& lType)
	:m_type(&lType)
{
}


WorldTile::~WorldTile(void)
{
}

bool WorldTile::isPassable(void) const
{
	return m_type->getPassable();
}
bool WorldTile::isTransparent(void) const
{
	return m_type->getTransparent();
}
std::string WorldTile::getTitle(void) const 
{
	return m_type->getTitle();
}
