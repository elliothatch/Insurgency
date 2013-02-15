#include "StdAfx.h"
#include "UIMenuList.h"


UIMenuList::UIMenuList(void)
	:m_options(), m_selection(0), m_accessible(true),
	 m_optionStorage()
{
}

UIMenuList::UIMenuList(std::vector<UIMenuOption*> options)
	:m_options(options), m_selection(0), m_accessible(true),
	 m_optionStorage()
{
}


UIMenuList::~UIMenuList(void)
{
}

void UIMenuList::pushNewMenuOption(std::unique_ptr<UIMenuList> menuList, std::unique_ptr<UIMenuOption> listOption)
{
	m_options.push_back(listOption.get());
	m_optionStorage.push_back(std::make_pair<std::unique_ptr<UIMenuList>,std::unique_ptr<UIMenuOption>>(
		std::move(menuList),std::move(listOption)));
}

void UIMenuList::eraseMenuOption(unsigned int index)
{
	m_options.erase(m_options.begin() + index);
	m_optionStorage.erase(m_optionStorage.begin() + index);
	if(m_selection >= static_cast<long int>(m_options.size()) && m_selection != 0)
		m_selection = m_options.size()-1;
	if(m_options.size() == 0)
		m_accessible = false;
}