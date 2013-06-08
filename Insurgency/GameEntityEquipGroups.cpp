#include "StdAfx.h"
#include "GameEntityEquipGroups.h"


GameEntityEquipGroups::GameEntityEquipGroups(void)
{
}


GameEntityEquipGroups::~GameEntityEquipGroups(void)
{
}

void GameEntityEquipGroups::addEquipGroup(GameEntityEquipGroups::EquipGroup equipGroup)
{
	m_equipGroups.push_back(equipGroup);
}
void GameEntityEquipGroups::setEquipGroups(std::vector<GameEntityEquipGroups::EquipGroup> equipGroups)
{
	m_equipGroups = equipGroups;
}
const std::vector<GameEntityEquipGroups::EquipGroup>& GameEntityEquipGroups::getEquipGroups() const
{
	return m_equipGroups;
}

std::string GameEntityEquipGroups::EquipGroup::getName() const
{
	if(m_name.size() != 0)
		return m_name;

	//no custom name - return a default name - summation of all equip slot names
	std::string retVal = "";
	for(auto slotIt(m_equipSlots.begin()); slotIt != m_equipSlots.end(); slotIt++)
	{
		retVal += getEquipSlotName(*slotIt);
		retVal += ", ";
	}
	retVal.pop_back();
	retVal.pop_back();
	return retVal;
}

//static
std::string GameEntityEquipGroups::getEquipSlotName(EntityEquipSlotID::E id)
{
	switch(id)
	{
	case EntityEquipSlotID::HeldLeft:
		return "In Left Hand";
	case EntityEquipSlotID::HeldRight:
		return "In Right Hand";
	case EntityEquipSlotID::Shirt:
		return "Shirt";
	case EntityEquipSlotID::Pants:
		return "Pants";
	case EntityEquipSlotID::Shoes:
		return "Shoes";
	case EntityEquipSlotID::Gloves:
		return "Gloves";
	case EntityEquipSlotID::HandLeft:
		return "On Left Hand";
	case EntityEquipSlotID::HandRight:
		return "On Right Hand";
	case EntityEquipSlotID::ForearmLeft:
		return "Left Forearm";
	case EntityEquipSlotID::ForearmRight:
		return "Right Forearm";
	case EntityEquipSlotID::ShoulderLeft:
		return "Left Shoulder";
	case EntityEquipSlotID::ShoulderRight:
		return "Right Shoulder";
	case EntityEquipSlotID::Neck:
		return "Neck";
	case EntityEquipSlotID::Head:
		return "Head";
	case EntityEquipSlotID::Eyes:
		return "Eyes";
	case EntityEquipSlotID::Chest:
		return "Chest";
	case EntityEquipSlotID::Abdomen:
		return "Abdomen";
	case EntityEquipSlotID::Groin:
		return "Groin";
	case EntityEquipSlotID::ThighLeft:
		return "Left Thigh";
	case EntityEquipSlotID::ThighRight:
		return "Right Thigh";
	case EntityEquipSlotID::ShinLeft:
		return "Left Shin";
	case EntityEquipSlotID::ShinRight:
		return "Right Shin";
	case EntityEquipSlotID::FootLeft:
		return "Left Foot";
	case EntityEquipSlotID::FootRight:
		return "Right Foot";
	}
	std::string name = "EntityEquipSlot" + id;
	return name;
}

//static
EntityEquipSlotID::E GameEntityEquipGroups::getEquipSlotID(const std::string& slotStr)
{
	static std::unordered_map<std::string, EntityEquipSlotID::E> s_equipSlotMap;
	if(s_equipSlotMap.size() == 0)
	{
		//init
		s_equipSlotMap["HeldRight"] = EntityEquipSlotID::HeldRight;
		s_equipSlotMap["HeldLeft"] = EntityEquipSlotID::HeldLeft;
		s_equipSlotMap["Shirt"] = EntityEquipSlotID::Shirt;
		s_equipSlotMap["Pants"] = EntityEquipSlotID::Pants;
		s_equipSlotMap["Shoes"] = EntityEquipSlotID::Shoes;
		s_equipSlotMap["Gloves"] = EntityEquipSlotID::Gloves;
		s_equipSlotMap["HandRight"] = EntityEquipSlotID::HandRight;
		s_equipSlotMap["HandLeft"] = EntityEquipSlotID::HandLeft;
		s_equipSlotMap["ForearmRight"] = EntityEquipSlotID::ForearmRight;
		s_equipSlotMap["ForearmLeft"] = EntityEquipSlotID::ForearmLeft;
		s_equipSlotMap["ShoulderRight"] = EntityEquipSlotID::ShoulderRight;
		s_equipSlotMap["ShoulderLeft"] = EntityEquipSlotID::ShoulderLeft;
		s_equipSlotMap["Neck"] = EntityEquipSlotID::Neck;
		s_equipSlotMap["Head"] = EntityEquipSlotID::Head;
		s_equipSlotMap["Eyes"] = EntityEquipSlotID::Eyes;
		s_equipSlotMap["Chest"] = EntityEquipSlotID::Chest;
		s_equipSlotMap["Abdomen"] = EntityEquipSlotID::Abdomen;
		s_equipSlotMap["Groin"] = EntityEquipSlotID::Groin;
		s_equipSlotMap["ThighRight"] = EntityEquipSlotID::ThighRight;
		s_equipSlotMap["ThighLeft"] = EntityEquipSlotID::ThighLeft;
		s_equipSlotMap["ShinRight"] = EntityEquipSlotID::ShinRight;
		s_equipSlotMap["ShinLeft"] = EntityEquipSlotID::ShinLeft;
		s_equipSlotMap["FootRight"] = EntityEquipSlotID::FootRight;
		s_equipSlotMap["FootLeft"] = EntityEquipSlotID::FootLeft;
	}

	std::unordered_map<std::string, EntityEquipSlotID::E>::iterator mapIt = s_equipSlotMap.find(slotStr);
	if(mapIt != s_equipSlotMap.end())
	{
		return mapIt->second;
	}
	else
	{
		printf("EQUIP SLOT ID NOT FOUND - %s", slotStr.c_str());
		return EntityEquipSlotID::Count;
	}
}