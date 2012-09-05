#pragma once
#include "iworldtiletypedef.h"
#include <array>
//NOTE: THIS CLASS HAS THE TILE TYPES HARDCODED IN
//CONSIDER CREATING A NEW CLASS THAT READS THE VALUES IN FROM A TEXT FILE AT LAUNCH
class WorldTileTypeDef :
	public IWorldTileTypeDef
{
	static const int kFloorValue = 0;
	static const int kHalfWallValue = 64;
    static const int kWallValue = 128;
    static const int kMaxTileTypes = 256;
public:
	WorldTileTypeDef(void);
	virtual ~WorldTileTypeDef(void);

	virtual const WorldTileType& getTileType(WorldTileTypeID lID) const;
private:
	std::array<WorldTileType, kMaxTileTypes> tileTypes;

};

