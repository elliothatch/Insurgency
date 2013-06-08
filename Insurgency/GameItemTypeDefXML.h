#pragma once
#include "IGameItemTypeDef.h"
#include "pugixml.hpp"
#include <vector>
#include <sstream>

class GameItemTypeDefXML : public IGameItemTypeDef
{
public:
	GameItemTypeDefXML(void);
	virtual ~GameItemTypeDefXML(void);

	virtual const GameItemType& getItemType(GameItemTypeID lTypeID) const;

private:
	std::vector<std::unique_ptr<GameItemType>> m_itemTypes;

};

