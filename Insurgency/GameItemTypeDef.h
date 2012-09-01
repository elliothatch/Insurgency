#pragma once
#include "igameitemtypedef.h"
class GameItemTypeDef :
	public IGameItemTypeDef
{
public:
	GameItemTypeDef(void);
	virtual ~GameItemTypeDef(void);

	virtual const GameItemType& getTileType(GameItemTypeID lTypeID) const;
private:
#define MAXITEMTYPES 256
	GameItemType itemTypes[MAXITEMTYPES];
};

