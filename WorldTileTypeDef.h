#pragma once
#include "iworldtiletypedef.h"
//NOTE: THIS CLASS HAS THE TILE TYPES HARDCODED IN
//CONSIDER CREATING A NEW CLASS THAT READS THE VALUES IN FROM A TEXT FILE AT LAUNCH
class WorldTileTypeDef :
	public IWorldTileTypeDef
{
public:
	WorldTileTypeDef(void);
	virtual ~WorldTileTypeDef(void);

	virtual const WorldTileType& getTileType(WorldTileTypeID lID) const;
private:
#define FLOOR 0
#define HALFWALL 64
#define WALL 128
#define MAXTILETYPES 256
	WorldTileType tileTypes[MAXTILETYPES];

};

