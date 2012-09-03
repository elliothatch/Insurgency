#pragma once
#include "WorldTile.h"
class WorldRegion
{
public:
#define REGIONSIZE 10

	WorldRegion(void);
	~WorldRegion(void);

	WorldTile* getTile(std::pair<int,int> loc);
	void setTile(std::pair<int,int> loc, WorldTile* lTile); //deletes old tile
	void save(void);
	void load(void);

	int getSize() const {return REGIONSIZE;}

private:
	WorldTile* tiles[REGIONSIZE][REGIONSIZE];

};

