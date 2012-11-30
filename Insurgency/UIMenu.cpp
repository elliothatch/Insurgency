#include "StdAfx.h"
#include "UIMenu.h"


UIMenu::UIMenu(void)
	:m_previousMenuList(nullptr),
	 m_currentMenuList(nullptr),
	 m_nextMenuList(nullptr),
	 m_branch(),
	 m_selection(0),
	 m_helpText("Help Text"),
	 m_hideChangeSelection(false)
{
}


UIMenu::~UIMenu(void)
{
}

void UIMenu::setTrunk(UIMenuList* menuList)
{
	m_currentMenuList = menuList;
	m_previousMenuList = nullptr;
	m_branch.clear();
	m_branch.push_back(menuList);
	update();
}

void UIMenu::select(int n)
{
	m_selection = n;
	m_currentMenuList->m_selection = n;
	if(m_currentMenuList->m_options.size())
	{
		if(m_currentMenuList->m_options[n]->m_target)
		{
			m_nextMenuList = m_currentMenuList->m_options[n]->m_target;
		} 
		else 
		{
			m_nextMenuList = nullptr;
		}
	}
	else
	{
		m_nextMenuList = nullptr;
	}
	//if(parent) 
	//	renderMenu();
	if(!m_hideChangeSelection) 
		changeSelection();
}

void UIMenu::stepRight()
{
	if(!(m_nextMenuList && !m_nextMenuList->m_accessible) && m_currentMenuList->m_options[m_selection]->m_active)
	{
		// walk forward
		if(m_nextMenuList)
		{
			m_branch.push_back(m_nextMenuList);
			m_previousMenuList = m_currentMenuList;
			m_currentMenuList = m_nextMenuList;	
		// nothing to walk forward to - call the executeSelection
		} 
		else 
		{
			executeSelection();
			int selectionStep = m_currentMenuList->m_options[m_currentMenuList->m_selection]->m_selectionStep;
			if(selectionStep == UIMenuOption::TRUNK) 
				setTrunk(m_branch[0]);
			else 
			{
				if(selectionStep == UIMenuOption::EXIT_MENU)
				{
					setTrunk(m_branch[0]);
				} 
				else 
				{
					// inspect the branch list for empty menu lists that will crash the walk back
					// upon finding one we drop out to the root menu
					for(int i = m_branch.size() - 1; i > -1; i--)
					{
						if(m_branch[i]->m_options.size() == 0)
						{
							setTrunk(m_branch[0]);
							return;
						}
					}
					// the step back and forth shakes out select events and updates the labels
					while(selectionStep--)
					{
						stepLeft();
					}
					stepRight();
				}
			}
		}
	}
}

void UIMenu::stepLeft()
{
	if(m_previousMenuList)
	{
		m_branch.pop_back();
		m_nextMenuList = m_currentMenuList;
		m_currentMenuList = m_previousMenuList;
		if(m_branch.size() > 1)
			m_previousMenuList = m_branch[m_branch.size() - 2];
		else
			m_previousMenuList = nullptr;
		update();
	}
}

void UIMenu::changeSelection()
{
	if(m_currentMenuList->m_options.size() == 0) 
		return;
	UIMenuOption* option = m_currentMenuList->m_options[m_selection];
	m_helpText = option->m_helpText;
}

void UIMenu::update()
{
	select(m_currentMenuList->m_selection);
}
