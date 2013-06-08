#include "StdAfx.h"
#include "GameItemTypeDefXML.h"


GameItemTypeDefXML::GameItemTypeDefXML(void)
	:m_itemTypes()
{
	//load xml file
	pugi::xml_document document;
	pugi::xml_parse_result loadResult = document.load_file("data/item_data.xml");
	if(loadResult.status != pugi::status_ok)
	{
		printf(loadResult.description());
		printf("ITEM LOADING ABORTED\n");
		return;
	}

	GameEntityActions defaultActions;
	defaultActions.addWorldAction(EntityActionID::PickUp);
	defaultActions.addInventoryAction(EntityActionID::Drop);
	defaultActions.addInventoryAction(EntityActionID::Equip);
	defaultActions.addEquippedAction(EntityActionID::Drop);
	defaultActions.addEquippedAction(EntityActionID::Unequip);

	//walk down xml file
	for(pugi::xml_node_iterator nodeIt = document.begin()->begin(); nodeIt != document.begin()->end(); nodeIt++)
	{
		
		std::unique_ptr<GameItemType> itemTypePtr(new GameItemType());
		GameItemType& itemType = *itemTypePtr.get();
		itemType.setTypeID(m_itemTypes.size());
		//names
		pugi::xml_node namesNode = nodeIt->child("Names");
		itemType.setLName(namesNode.child_value("Long"));
		itemType.setSName(namesNode.child_value("Short"));
		itemType.setDName(namesNode.child_value("Description"));
		//TODO:Parse class id and set enum
		itemType.setClassID(GameItemClassID::AssaultRifle01);

		//TODO:Implement action parsing
		itemType.setGameEntityActions(defaultActions);

		//equip groups
		GameEntityEquipGroups equipGroups;
		//iterate through all groups
		for(pugi::xml_node_iterator groupIt = nodeIt->child("EquipGroups").begin(); 
				groupIt != nodeIt->child("EquipGroups").end(); groupIt++)
		{
			GameEntityEquipGroups::EquipGroup equipGroup;
			if(groupIt->child("Name"))
				equipGroup.setName(groupIt->child_value("Name"));
			std::string slotsStr = groupIt->child_value("Slots");
			//split slots into seperate strings, comma delimited
			std::vector<std::string> slotsStrings;
			std::stringstream ss(slotsStr);
			std::string str;
			while (std::getline(ss, str, ',')) 
			{
				 slotsStrings.push_back(str);
			}
			for(auto strIt = slotsStrings.begin(); strIt != slotsStrings.end(); strIt++)
			{
				equipGroup.m_equipSlots.insert(GameEntityEquipGroups::getEquipSlotID(*strIt));
			}
			equipGroups.addEquipGroup(equipGroup);
		}
		itemType.setGameEntityEquipGroups(equipGroups);

		m_itemTypes.push_back(std::move(itemTypePtr));
	}
	
}


GameItemTypeDefXML::~GameItemTypeDefXML(void)
{
}

const GameItemType& GameItemTypeDefXML::getItemType(GameItemTypeID lTypeID) const
{
	return *m_itemTypes.at(lTypeID);
}