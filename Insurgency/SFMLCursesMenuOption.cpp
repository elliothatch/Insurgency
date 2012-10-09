#include "StdAfx.h"
#include "SFMLCursesMenuOption.h"


SFMLCursesMenuOption::SFMLCursesMenuOption(std::string name, SFMLCursesMenuList* target = nullptr, bool active = true)
	:m_name(name), m_helpText(), m_target(target), m_active(active), m_visited(true), m_hidden(true), m_selectionStep(TRUNK)
{
}


SFMLCursesMenuOption::~SFMLCursesMenuOption(void)
{
}
