#include "StdAfx.h"
#include "WorldRegion.h"


WorldRegion::WorldRegion(void)
{
	for(int i = 0; i<REGIONSIZE; i++)
	{
		for(int j = 0; j<REGIONSIZE; j++)
		{
			if(tiles[i][j])
			{
			tiles[i][j] = NULL;
			}
		}
	}
}


WorldRegion::~WorldRegion(void)
{
	for(int i = 0; i<REGIONSIZE; i++)
	{
		for(int j = 0; j<REGIONSIZE; j++)
		{
			if(tiles[i][j])
			{
			delete tiles[i][j];
			}
		}
	}
}

WorldTile* WorldRegion::getTile(std::pair<int,int> loc)
{
	if(loc.first < REGIONSIZE && loc.second < REGIONSIZE)
		return tiles[loc.first][loc.second];
	else
		return NULL;
}

void WorldRegion::setTile(std::pair<int,int> loc, WorldTile* tile)
{
	if(tiles[loc.first][loc.second])
	{
		delete tiles[loc.first][loc.second];
		tiles[loc.first][loc.second] = NULL;
	}
	tiles[loc.first][loc.second] = tile;
}

void WorldRegion::save(void)
{
}

void WorldRegion::load(void)
{
}