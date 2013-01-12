#include "stdafx.h"
#include "UIMenuOption_EntityActionDef.h"

std::map<EntityActionID::E, UIMenuOption> UIMenuOption_EntityActionDef::m_menuOptions;

UIMenuOption* UIMenuOption_EntityActionDef::getMenuOption(EntityActionID::E id)
{
	if(m_menuOptions.size() == 0)
	{
		//initialize
		for(unsigned int i = 0; i<EntityActionID::Count; i++)
		{
			EntityActionID::E curID = static_cast<EntityActionID::E>(i);
			std::string name = getActionName(curID);
			std::pair<EntityActionID::E,UIMenuOption> option(curID,UIMenuOption(name));
			option.second.m_selectionStep = getSelectionStep(curID);
			m_menuOptions.insert(option);
		}
	}
	return &m_menuOptions.find(id)->second;
}

std::string UIMenuOption_EntityActionDef::getActionName(EntityActionID::E id)
{
	switch(id)
	{
	case EntityActionID::PickUp:
		return "Pick Up";
	case EntityActionID::Drop:
		return "Drop";
	case EntityActionID::Equip:
		return "Equip";
	case EntityActionID::Unequip:
		return "Unequip";
	}
	std::string name = "EntityAction" + id;
	return name;
}

int UIMenuOption_EntityActionDef::getSelectionStep(EntityActionID::E id)
{
	switch(id)
	{
	case EntityActionID::Drop:
		return 2;
	default:
		return 1;
	}
}