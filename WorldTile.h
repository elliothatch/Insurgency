#pragma once
#include "iworldtile.h"

class WorldTile :
	public IWorldTile
{
public:
	WorldTile(const WorldTileType& lType);
	~WorldTile(void);

	virtual bool isPassable(void) {return type.getPassable();}
	virtual bool isTransparent(void) {return type.getTransparent();}
	virtual std::string getTitle(void) {return type.getTitle();}

	//temp curses test code
	virtual char getDispCh(void) {return type.getDispCh();}

private:
	const WorldTileType& type;
};

