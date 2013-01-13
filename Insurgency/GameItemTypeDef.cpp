#include "StdAfx.h"
#include "GameItemTypeDef.h"


GameItemTypeDef::GameItemTypeDef(void)
{
	GameEntityActions defaultActions;
	defaultActions.addWorldAction(EntityActionID::PickUp);
	defaultActions.addInventoryAction(EntityActionID::Drop);
	defaultActions.addInventoryAction(EntityActionID::Equip);
	defaultActions.addEquippedAction(EntityActionID::Drop);
	defaultActions.addEquippedAction(EntityActionID::Unequip);
	for(int i = 0; i<kMaxItemTypes; i++)
	{
		itemTypes[i].setTypeID(i);
		itemTypes[i].setGameEntityActions(defaultActions);
	}
	itemTypes[1].setLName("kalashnikov");
	itemTypes[1].setSName("AK-47");
	itemTypes[1].setDName("AK-47");
	itemTypes[1].setClassID(GameItemClassID::AssaultRifle01);

	itemTypes[2].setLName("P90");
	itemTypes[2].setSName("P90");
	itemTypes[2].setDName("P90");
	itemTypes[2].setClassID(GameItemClassID::AssaultRifle01);
}


GameItemTypeDef::~GameItemTypeDef(void)
{
}

const GameItemType& GameItemTypeDef::getTileType(GameItemTypeID lTypeID) const
{
	return itemTypes[lTypeID];
}