#pragma once
#include <string>
#include "WorldTileType.h"

class WorldTile
{
public:
	WorldTile(const WorldTileType& lType);
	~WorldTile(void);

	bool isPassable(void) {return type.getPassable();}
	bool isTransparent(void) {return type.getTransparent();}
	std::string getTitle(void) {return type.getTitle();}

	//temp curses test code
	char getDispCh(void) {return type.getDispCh();}

private:
	const WorldTileType& type;
};

