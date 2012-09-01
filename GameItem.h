#pragma once
#include "gameentity.h"
#include "GameItemType.h"
class GameItem :
	public GameEntity
{
public:
	GameItem(const GameItemType& lItemType, std::pair<int,int> loc);
	virtual ~GameItem(void);

	//getters
	//NOTE: probably won't even need to store type and class in the item
	GameItemTypeID getType(void) const {return m_type;}
	GameItemClassID getClass(void) const {return m_class;}

private:
	GameItemTypeID m_type;
	GameItemClassID m_class;
};

