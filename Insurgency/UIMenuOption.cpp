#include "StdAfx.h"
#include "UIMenuOption.h"


UIMenuOption::UIMenuOption(std::string name, UIMenuList* target, bool active)
	:m_name(name), m_helpText(), m_target(target), m_active(active), m_visited(true), m_hidden(true), m_selectionStep(TRUNK)
{
}


UIMenuOption::~UIMenuOption(void)
{
}
