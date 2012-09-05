#pragma once
#include <array>
#include "igameitemtypedef.h"
class GameItemTypeDef :
	public IGameItemTypeDef
{
	static const int kMaxItemTypes = 256;
public:
	GameItemTypeDef(void);
	virtual ~GameItemTypeDef(void);

	virtual const GameItemType& getTileType(GameItemTypeID lTypeID) const;
private:
	std::array<GameItemType, kMaxItemTypes> itemTypes;
};

