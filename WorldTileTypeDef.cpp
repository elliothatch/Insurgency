#include "StdAfx.h"
#include "WorldTileTypeDef.h"


WorldTileTypeDef::WorldTileTypeDef(void)
{
	//setting tile types
	//---------\\
	//TILE TYPES
	//---------//
	//0-63 - ground
	//64-127 - "half-walls" - items can occupy space (revise?)
	//128-255 - wall

	//Standard Cases - initialize
	//Floors
	for(WorldTileTypeID i = FLOOR; i<HALFWALL; i++)
	{
		tileTypes[i].setPassable(1);
		tileTypes[i].setTransparent(1);
		//temp
		tileTypes[i].setDispCh('.');
	}
	//Half-walls
	for(int i = HALFWALL; i<WALL; i++)
	{
		tileTypes[i].setPassable(0);
		tileTypes[i].setTransparent(1);
		//temp
		tileTypes[i].setDispCh('-');
		//Half-walls break to their respective ground
		//tileTypes[i].breakChild = i-HALFWALL;
		//tileTypes[i].dispCh = '-';
		//tileTypes[i].maxDamage = 50;
	}
	//Walls
		for(int i = WALL; i<MAXTILETYPES; i++)
	{
		tileTypes[i].setPassable(0);
		tileTypes[i].setTransparent(0);
		//temp
		tileTypes[i].setDispCh('#');
		//Walls break to their respective half-wall
		//tileTypes[i].breakChild = i-HALFWALL;
		//tileTypes[i].dispCh = '#';
		//tileTypes[i].maxDamage = 80;
	}

	//Names
	tileTypes[0].setTitle("dirt ground");
	tileTypes[1].setTitle("street");
	tileTypes[2].setTitle("concrete floor");
	//...
	tileTypes[HALFWALL].setTitle("dirt mound");
	tileTypes[HALFWALL+1].setTitle("asphalt mound");
	tileTypes[HALFWALL+2].setTitle("concrete half-wall");
	//...
	tileTypes[WALL].setTitle("dirt wall");
	tileTypes[WALL+1].setTitle("asphalt wall");
	tileTypes[WALL+2].setTitle("concrete wall");

	//END TILE TYPES

}


WorldTileTypeDef::~WorldTileTypeDef(void)
{
}

const WorldTileType& WorldTileTypeDef::getTileType(WorldTileTypeID lID) const
{
	return tileTypes[lID];
}