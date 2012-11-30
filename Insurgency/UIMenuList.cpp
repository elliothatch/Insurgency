#include "StdAfx.h"
#include "UIMenuList.h"


UIMenuList::UIMenuList(void)
	:m_options(), m_selection(0), m_accessible(true)
{
}

UIMenuList::UIMenuList(std::vector<UIMenuOption*> options)
	:m_options(options), m_selection(0), m_accessible(true)
{
}


UIMenuList::~UIMenuList(void)
{
}
