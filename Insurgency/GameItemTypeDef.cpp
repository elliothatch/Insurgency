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

	GameEntityEquipGroups assaultRifleEquipGroups;
	assaultRifleEquipGroups.addEquipGroup(equipBothHands);
	GameEntityEquipGroups handgunEquipGroups;
	handgunEquipGroups.addEquipGroup(equipBothHands);
	handgunEquipGroups.addEquipGroup(EntityEquipSlotID::HeldRight);
	handgunEquipGroups.addEquipGroup(EntityEquipSlotID::HeldLeft);

	GameEntityEquipGroups::EquipGroup equipPants;
	equipPants.m_equipSlots.insert(EntityEquipSlotID::Groin);
	equipPants.m_equipSlots.insert(EntityEquipSlotID::ThighRight);
	equipPants.m_equipSlots.insert(EntityEquipSlotID::ThighLeft);
	equipPants.m_equipSlots.insert(EntityEquipSlotID::ShinRight);
	equipPants.m_equipSlots.insert(EntityEquipSlotID::ShinLeft);
	GameEntityEquipGroups pantsEquipGroups;
	pantsEquipGroups.addEquipGroup(equipPants);

	itemTypes[1].setLName("AK-47");
	itemTypes[1].setSName("AK-47");
	itemTypes[1].setDName("AK-47");
	itemTypes[1].setClassID(GameItemClassID::AssaultRifle01);
	itemTypes[1].setGameEntityEquipGroups(assaultRifleEquipGroups);

	itemTypes[2].setLName("P90");
	itemTypes[2].setSName("P90");
	itemTypes[2].setDName("P90");
	itemTypes[2].setClassID(GameItemClassID::AssaultRifle01);
	itemTypes[2].setGameEntityEquipGroups(assaultRifleEquipGroups);

	itemTypes[3].setLName("1911");
	itemTypes[3].setSName("1911");
	itemTypes[3].setDName("1911");
	itemTypes[3].setClassID(GameItemClassID::Handgun01);
	itemTypes[3].setGameEntityEquipGroups(handgunEquipGroups);

	itemTypes[4].setLName("Cargo Pants");
	itemTypes[4].setSName("Cargo Pants");
	itemTypes[4].setDName("Cargo Pants");
	itemTypes[4].setClassID(GameItemClassID::Pants01);
	itemTypes[4].setGameEntityEquipGroups(pantsEquipGroups);
}


GameItemTypeDef::~GameItemTypeDef(void)
{
}

const GameItemType& GameItemTypeDef::getTileType(GameItemTypeID lTypeID) const
{
	return itemTypes[lTypeID];
}