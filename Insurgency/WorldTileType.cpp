#include "stdafx.h"
#include "WorldTileType.h"

WorldTileType::WorldTileType()
	:m_passable(true), m_transparent(true),
	m_title("Title"), m_dispCh('.')
	{
	}

WorldTileType::~WorldTileType(void)
{
}

bool WorldTileType::getPassable() const
{
	return m_passable;
}
bool WorldTileType::getTransparent() const
{
	return m_transparent;
}
std::string WorldTileType::getTitle() const
{
	return m_title;
}
//temp
char WorldTileType::getDispCh() const
{
	return m_dispCh;
}
//setters
void WorldTileType::setPassable(bool val)
{
	m_passable = val;
}
void WorldTileType::setTransparent(bool val) 
{
	m_transparent = val;
}
void WorldTileType::setTitle(std::string lTitle)
{
	m_title = lTitle;
}
//temp
void WorldTileType::setDispCh(char lChar)
{
	m_dispCh = lChar;
}