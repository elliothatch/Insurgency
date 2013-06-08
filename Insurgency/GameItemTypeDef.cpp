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
	GameEntityEquipGroups::EquipGroup equipBothHands;
	equipBothHands.m_equipSlots.insert(EntityEquipSlotID::HeldRight);
	equipBothHands.m_equipSlots.insert(EntityEquipSlotID::HeldLeft);
	equipBothHands.setName("Both Hands");

	GameEntityEquipGroups assaultRifleEquipGroups;
	assaultRifleEquipGroups.addEquipGroup(equipBothHands);
	GameEntityEquipGroups handgunEquipGroups;
	handgunEquipGroups.addEquipGroup(equipBothHands);
	handgunEquipGroups.addEquipGroup(EntityEquipSlotID::HeldRight);
	handgunEquipGroups.addEquipGroup(EntityEquipSlotID::HeldLeft);

	GameEntityEquipGroups::EquipGroup equipPants;
	equipPants.m_equipSlots.insert(EntityEquipSlotID::Pants);
	GameEntityEquipGroups pantsEquipGroups;
	pantsEquipGroups.addEquipGroup(equipPants);

	itemTypes[0].setLName("AK-47");
	itemTypes[0].setSName("AK-47");
	itemTypes[0].setDName("AK-47");
	itemTypes[0].setClassID(GameItemClassID::AssaultRifle01);
	itemTypes[0].setGameEntityEquipGroups(assaultRifleEquipGroups);

	itemTypes[1].setLName("P90");
	itemTypes[1].setSName("P90");
	itemTypes[1].setDName("P90");
	itemTypes[1].setClassID(GameItemClassID::AssaultRifle01);
	itemTypes[1].setGameEntityEquipGroups(assaultRifleEquipGroups);

	itemTypes[2].setLName("M1911");
	itemTypes[2].setSName("M1911");
	itemTypes[2].setDName("M1911");
	itemTypes[2].setClassID(GameItemClassID::Handgun01);
	itemTypes[2].setGameEntityEquipGroups(handgunEquipGroups);

	itemTypes[3].setLName("Parachute Pants");
	itemTypes[3].setSName("Parachute Pants");
	itemTypes[3].setDName("Parachute Pants");
	itemTypes[3].setClassID(GameItemClassID::Pants01);
	itemTypes[3].setGameEntityEquipGroups(pantsEquipGroups);
}


GameItemTypeDef::~GameItemTypeDef(void)
{
}

const GameItemType& GameItemTypeDef::getItemType(GameItemTypeID lTypeID) const
{
	return itemTypes[lTypeID];
}