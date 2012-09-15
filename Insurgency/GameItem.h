#pragma once
#include "gameentity.h"
#include "GameItemType.h"
#include <memory>
class GameItem :
	public GameEntity
{
public:
	typedef std::unique_ptr<GameItem> ptr;
	GameItem(const GameItemType& lItemType);
	virtual ~GameItem(void);

	//getters
	//NOTE: probably won't even need to store type and class in the item
	GameItemTypeID getType(void) const;
	GameItemClassID::E getClass(void) const;

private:
	GameItemTypeID m_type;
	GameItemClassID::E m_class;
};

