#include "StdAfx.h"
#include "SFMLCursesMenuList.h"


SFMLCursesMenuList::SFMLCursesMenuList(void)
	:m_options(), m_selection(0), m_accessible(true)
{
}

SFMLCursesMenuList::SFMLCursesMenuList(std::vector<SFMLCursesMenuOption*> options)
	:m_options(options), m_selection(0), m_accessible(true)
{
}


SFMLCursesMenuList::~SFMLCursesMenuList(void)
{
}
