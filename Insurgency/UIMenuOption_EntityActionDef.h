#pragma once
#include "UIMenuOption.h"
#include "GameEntityActions.h"
#include <map>

class UIMenuOption_EntityActionDef
{
public:
	static UIMenuOption* getMenuOption(EntityActionID::E id);
	static std::string getActionName(EntityActionID::E id);
private:
	static std::map<EntityActionID::E, UIMenuOption> m_menuOptions;

};