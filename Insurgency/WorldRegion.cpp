#include "StdAfx.h"
#include "WorldRegion.h"


WorldRegion::WorldRegion(void)
{
}

WorldRegion::~WorldRegion(void)
{
}

WorldTile& WorldRegion::getTile(std::pair<int,int> loc)
{

	if(!(loc.first < kRegionSize && loc.second < kRegionSize))
		throw std::out_of_range("Out of Range");
		
		return *tiles[loc.first][loc.second];
}

void WorldRegion::setTile(std::pair<int,int> loc, WorldTile::ptr tile)
{
	if(!(loc.first < kRegionSize && loc.second < kRegionSize))
		throw std::out_of_range("Out of Range");

	tiles[loc.first][loc.second] = std::move(tile);
}

void WorldRegion::save(void)
{
}

void WorldRegion::load(void)
{
}