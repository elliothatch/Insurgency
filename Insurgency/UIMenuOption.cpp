#include "StdAfx.h"
#include "UIMenuOption.h"


UIMenuOption::UIMenuOption(const std::string& name, UIMenuList* target, const std::string& tag, bool active)
	:m_name(name), m_helpText(), m_tag(tag), m_target(target), m_active(active), m_visited(true), m_hidden(true), m_selectionStep(TRUNK)
{
}


UIMenuOption::~UIMenuOption(void)
{
}
