#pragma once
#include "WorldTile.h"
#include <memory>
#include <array>
class WorldRegion
{
public:
	typedef std::unique_ptr<WorldRegion> ptr;
#define REGIONSIZE 10

	WorldRegion(void);
	~WorldRegion(void);

	WorldTile& getTile(std::pair<int,int> loc);
	void setTile(std::pair<int,int> loc, WorldTile::ptr lTile); //deletes old tile
	void save(void);
	void load(void);

	int getSize() const {return REGIONSIZE;}

private:
	WorldTile::ptr tiles[REGIONSIZE][REGIONSIZE];

};

