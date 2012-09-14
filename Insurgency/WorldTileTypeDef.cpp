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
	for(WorldTileTypeID i = kFloorValue; i<kHalfWallValue; i++)
	{
		tileTypes[i].setPassable(1);
		tileTypes[i].setTransparent(1);
	}
	//Half-walls
	for(int i = kHalfWallValue; i<kWallValue; i++)
	{
		tileTypes[i].setPassable(0);
		tileTypes[i].setTransparent(1);
		//Half-walls break to their respective ground
		//tileTypes[i].breakChild = i-kHalfWallValue;
		//tileTypes[i].dispCh = '-';
		//tileTypes[i].maxDamage = 50;
	}
	//Walls
		for(int i = kWallValue; i<kMaxTileTypes; i++)
	{
		tileTypes[i].setPassable(0);
		tileTypes[i].setTransparent(0);
		//Walls break to their respective half-wall
		//tileTypes[i].breakChild = i-kHalfWallValue;
		//tileTypes[i].dispCh = '#';
		//tileTypes[i].maxDamage = 80;
	}

	//Names
	tileTypes[0].setTitle("dirt ground");
	tileTypes[1].setTitle("street");
	tileTypes[2].setTitle("concrete floor");
	//...
	tileTypes[kHalfWallValue].setTitle("dirt mound");
	tileTypes[kHalfWallValue+1].setTitle("asphalt mound");
	tileTypes[kHalfWallValue+2].setTitle("concrete half-wall");
	//...
	tileTypes[kWallValue].setTitle("dirt wall");
	tileTypes[kWallValue+1].setTitle("asphalt wall");
	tileTypes[kWallValue+2].setTitle("concrete wall");

	//END TILE TYPES

}


WorldTileTypeDef::~WorldTileTypeDef(void)
{
}

const WorldTileType& WorldTileTypeDef::getTileType(WorldTileTypeID lID) const
{
	return tileTypes[lID];
}