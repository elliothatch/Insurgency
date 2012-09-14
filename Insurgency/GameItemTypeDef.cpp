#include "StdAfx.h"
#include "GameItemTypeDef.h"


GameItemTypeDef::GameItemTypeDef(void)
{
	for(int i = 0; i<kMaxItemTypes; i++)
	{
		itemTypes[i].setTypeID(i);
	}
	itemTypes[1].setLName("kalashnikov");
	itemTypes[1].setSName("AK-47");
	itemTypes[1].setDName("AK-47");
	itemTypes[1].setClassID(GameItemClassID::AssaultRifle01);
}


GameItemTypeDef::~GameItemTypeDef(void)
{
}

const GameItemType& GameItemTypeDef::getTileType(GameItemTypeID lTypeID) const
{
	return itemTypes[lTypeID];
}