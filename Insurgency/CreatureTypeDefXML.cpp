#include "StdAfx.h"
#include "CreatureTypeDefXML.h"


CreatureTypeDefXML::CreatureTypeDefXML(void)
	:m_creatureTypes()
{
	//load xml file
	pugi::xml_document document;
	pugi::xml_parse_result loadResult = document.load_file("data/creature_data.xml");
	if(loadResult.status != pugi::status_ok)
	{
		printf(loadResult.description());
		printf("CREATURE LOADING ABORTED\n");
		return;
	}

	//walk down xml file
	for(pugi::xml_node_iterator nodeIt = document.begin()->begin(); nodeIt != document.begin()->end(); nodeIt++)
	{
		CreatureType creatureType;
		creatureType.setTypeID(m_creatureTypes.size());
		//names
		pugi::xml_node namesNode = nodeIt->child("Names");
		creatureType.setLName(namesNode.child_value("Long"));
		creatureType.setSName(namesNode.child_value("Short"));
		creatureType.setDName(namesNode.child_value("Description"));
		//TODO:Parse class id and set enum
		creatureType.setClassID(CreatureClassID::Insurgent01);

		pugi::xml_node statsNode = nodeIt->child("Stats");
		creatureType.setSpeed(atoi(statsNode.child_value("Speed")));
		creatureType.setStrength(atoi(statsNode.child_value("Strength")));

		//components
		//TODO:push out EntityTypeDef common functions into another class e.g. names, components, etc.
		pugi::xml_node componentsNode = nodeIt->child("Components");
		for(pugi::xml_node_iterator componentNodeIt(componentsNode.begin()); componentNodeIt != componentsNode.end(); componentNodeIt++)
		{
			std::string componentName(componentNodeIt->name());
			if(componentName == EntityComponentFactory::IDToString(EntityComponentID::Inventory))
			{
				creatureType.addComponent(std::unique_ptr<InventoryComponent>(new InventoryComponent()));
			}
			if(componentName == EntityComponentFactory::IDToString(EntityComponentID::EquipSlots))
			{
				std::unique_ptr<EquipSlotsComponent> equipSlots(new EquipSlotsComponent());
				std::string equipSlotsStr = componentNodeIt->child_value();
				if(equipSlotsStr.substr(0,6) == "Preset")
				{
					//TODO: SET UP PRESETS IN AN XML FILE
					if(std::string(equipSlotsStr).substr(6,equipSlotsStr.length() - 6) == "Human")
					{
						for(int j = 0; j<EntityEquipSlotID::Count; j++)
						{
							equipSlots->addEquipSlot(EntityEquipSlotID::E(j));
						}
					}
				}
				creatureType.addComponent(std::move(equipSlots));
			}
		}
		
		/*
		creatureType.addComponent(std::unique_ptr<InventoryComponent> (new InventoryComponent()));
		std::unique_ptr<EquipSlotsComponent> equip1(new EquipSlotsComponent());
		for(int j = 0; j<EntityEquipSlotID::Count; j++)
		{
			equip1->addEquipSlot(EntityEquipSlotID::E(j));
		}
		creatureType.addComponent(std::move(equip1));
		*/
		m_creatureTypes.push_back(std::move(creatureType));
	}
}


CreatureTypeDefXML::~CreatureTypeDefXML(void)
{
}

const CreatureType& CreatureTypeDefXML::getCreatureType(CreatureTypeID lTypeID) const
{
	return m_creatureTypes.at(lTypeID);
}