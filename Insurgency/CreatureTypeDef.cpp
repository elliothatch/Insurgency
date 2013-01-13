#include "StdAfx.h"
#include "CreatureTypeDef.h"


CreatureTypeDef::CreatureTypeDef(void)
{
	for(int i = 0; i<kMaxCreatureTypes; i++)
	{
		creatureTypes[i].setTypeID(i);
		std::unique_ptr<InventoryComponent> inv1(new InventoryComponent());
		std::unique_ptr<EquipSlotsComponent> equip1(new EquipSlotsComponent());
		for(int j = 0; j<EquipSlotsComponent::SlotID::count; j++)
		{
			equip1->addEquipSlot(EquipSlotsComponent::SlotID::E(j));
		}
		creatureTypes[i].addComponent(std::move(inv1));
		creatureTypes[i].addComponent(std::move(equip1));
	}
	creatureTypes[1].setLName("insurgent");
	creatureTypes[1].setSName("Elliot Hatch");
	creatureTypes[1].setDName("insurgent");
	creatureTypes[1].setClassID(CreatureClassID::Insurgent01);
	creatureTypes[1].setSpeed(5);
	creatureTypes[1].setStrength(6);
}


CreatureTypeDef::~CreatureTypeDef(void)
{
}

const CreatureType& CreatureTypeDef::getCreatureType(CreatureTypeID lTypeID) const
{
	return creatureTypes[lTypeID];
}