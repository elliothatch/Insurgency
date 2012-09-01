#pragma once
#include "iworldregion.h"
#include "WorldTile.h"
class WorldRegion :
	public IWorldRegion
{
public:
#define REGIONSIZE 10

	WorldRegion(void);
	virtual ~WorldRegion(void);

	virtual IWorldTile* getTile(std::pair<int,int> loc);
	virtual void setTile(std::pair<int,int> loc, IWorldTile* lTile); //deletes old tile
	virtual void save(void);
	virtual void load(void);

	virtual int getSize() const {return REGIONSIZE;}

private:
	IWorldTile* tiles[REGIONSIZE][REGIONSIZE];

};

