#include "StdAfx.h"
#include "SFMLUIMenu.h"


SFMLUIMenu::SFMLUIMenu(const sf::Window& window)
	:SFMLGUIElement(window),
	 m_helpTextBox(m_window, sf::Vector2i(10,30)),
	 m_UIMenu(nullptr),
	 m_selection(0),
	 m_branchLevel(0),
	 m_selectionTextColor(sf::Color::Black),
	 m_selectionBackgroundColor(sf::Color::White),
	 m_textColor(sf::Color::White),
	 m_backgroundColor(sf::Color::Black),
	 m_inaccessibleTextColorModifier(100,100,100,255),
	 m_inaccessibleBackgroundColorModifier(100,100,100,255)
{
}


SFMLUIMenu::~SFMLUIMenu(void)
{
}

void SFMLUIMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	for(std::vector<std::vector<SFMLCursesTextBox>>::const_iterator vecIt(m_menuOptionTextBoxes.begin()); vecIt != m_menuOptionTextBoxes.end(); vecIt++)
	{
		for(std::vector<SFMLCursesTextBox>::const_iterator boxIt(vecIt->begin()); boxIt != vecIt->end(); boxIt++)
		{
			target.draw(*boxIt, states);
		}
	}
	target.draw(m_helpTextBox, states);
}

void SFMLUIMenu::moveSelection(int s)
{
	//restore color of old option
	sf::Color textColor = m_textColor;
	sf::Color backgroundColor = m_backgroundColor;
	if(!getMenuOptionAccessible(m_UIMenu->m_currentMenuList->m_options[m_selection]))
	{
		textColor *= m_inaccessibleTextColorModifier;
		backgroundColor *= m_inaccessibleBackgroundColorModifier;
	}
	m_menuOptionTextBoxes[m_branchLevel][m_selection].setTextColor(textColor);
	m_menuOptionTextBoxes[m_branchLevel][m_selection].setBackgroundColor(backgroundColor);

	//remove old options
	if(m_menuOptionTextBoxes.size() > m_UIMenu->m_branch.size())
	{
		m_menuOptionTextBoxes.pop_back();
	}

	m_selection = s;
	m_UIMenu->select(m_selection);
	
	//reuse color variables
	textColor = m_selectionTextColor;
	backgroundColor = m_selectionBackgroundColor;
	if(!getMenuOptionAccessible(m_UIMenu->m_currentMenuList->m_options[m_selection]))
	{
		textColor *= m_inaccessibleTextColorModifier;
		backgroundColor *= m_inaccessibleBackgroundColorModifier;
	}

	m_menuOptionTextBoxes[m_branchLevel][m_selection].setTextColor(textColor);
	m_menuOptionTextBoxes[m_branchLevel][m_selection].setBackgroundColor(backgroundColor);

	//add new options
	if(getMenuListOptionAccessible(m_UIMenu->m_currentMenuList->m_options[m_selection]))
	{
		addMenuListTextBox(m_UIMenu->m_nextMenuList,m_branchLevel+1, false);
	}

	m_helpTextBox.setText(m_UIMenu->m_helpText);
}

void SFMLUIMenu::moveCursorUp()
{
	if(m_selection == 0 || m_UIMenu->m_currentMenuList->m_options.size() == 1)
		moveSelection(m_UIMenu->m_currentMenuList->m_options.size() - 1);
	else
		moveSelection(m_selection-1);
}
void SFMLUIMenu::moveCursorDown()
{
	if(m_selection ==  static_cast<int>(m_UIMenu->m_currentMenuList->m_options.size() - 1) || 
			m_UIMenu->m_currentMenuList->m_options.size() == 1)
		moveSelection(0);
	else
		moveSelection(m_selection+1);
}
void SFMLUIMenu::selectCursor()
{
	int lastBranchLevel = m_branchLevel;
	m_UIMenu->stepRight();
	m_branchLevel = m_UIMenu->m_branch.size()-1;
	m_selection = m_UIMenu->m_currentMenuList->m_selection;
	m_helpTextBox.setText(m_UIMenu->m_helpText);
	if(m_branchLevel > lastBranchLevel)
	{
		setMenuListTextBoxColors(m_UIMenu->m_previousMenuList,m_branchLevel-1, false);
		setMenuListTextBoxColors(m_UIMenu->m_currentMenuList,m_branchLevel, true);
		if(getMenuListOptionAccessible(m_UIMenu->m_currentMenuList->m_options[m_selection]))
		{
			addMenuListTextBox(m_UIMenu->m_nextMenuList, m_branchLevel+1, false);
		}
	}
	else
	{
		updateMenus();
	}
}
bool SFMLUIMenu::stepBack()
{
	if(m_UIMenu->m_previousMenuList)
	{
		if(getMenuListOptionAccessible(m_UIMenu->m_currentMenuList->m_options[m_selection]))
		{
			m_menuOptionTextBoxes.pop_back();
		}
		m_UIMenu->stepLeft();
		m_selection = m_UIMenu->m_currentMenuList->m_selection;
		m_branchLevel = m_UIMenu->m_branch.size()-1;
		m_helpTextBox.setText(m_UIMenu->m_helpText);
		if(getMenuListOptionAccessible(m_UIMenu->m_currentMenuList->m_options[m_selection]))
		{
			setMenuListTextBoxColors(m_UIMenu->m_nextMenuList,m_branchLevel+1, false);
		}
		setMenuListTextBoxColors(m_UIMenu->m_currentMenuList,m_branchLevel, true);
		return true;
	}
	return false;
}

void SFMLUIMenu::updateMenus()
{
	m_menuOptionTextBoxes.clear();
	for(std::vector<UIMenuList*>::iterator listIt(m_UIMenu->m_branch.begin()); listIt != m_UIMenu->m_branch.end(); listIt++)
	{
		bool accessible = false;
		if(listIt+1 == m_UIMenu->m_branch.end())
			accessible = true;
		int listIndex = listIt-m_UIMenu->m_branch.begin();	
		addMenuListTextBox(*listIt, listIndex, accessible);
	}
	if(getMenuListOptionAccessible(m_UIMenu->m_currentMenuList->m_options[m_selection]))
		addMenuListTextBox(m_UIMenu->m_nextMenuList, m_branchLevel+1, false);
	m_helpTextBox.setText(m_UIMenu->m_helpText);
}

void SFMLUIMenu::addMenuListTextBox(UIMenuList* list, int branchLevel, bool accessible)
{
	m_menuOptionTextBoxes.push_back(std::vector<SFMLCursesTextBox>());
	std::vector<UIMenuOption*>& menuOptions = list->m_options;
	for(std::vector<UIMenuOption*>::iterator optionIt(menuOptions.begin()); optionIt != menuOptions.end(); optionIt++)
	{
		int optionIndex = optionIt - menuOptions.begin();
		SFMLCursesTextBox textBox(m_window, sf::Vector2i(1,20));
		sf::Color textColor = m_textColor;
		sf::Color backgroundColor = m_backgroundColor;
		if(list->m_selection == optionIndex)
		{
			textColor = m_selectionTextColor;
			backgroundColor = m_selectionBackgroundColor;
		}
		if(!getMenuOptionAccessible(*optionIt))
		{
			textColor *= m_inaccessibleTextColorModifier;
			backgroundColor *= m_inaccessibleBackgroundColorModifier;
		}
		if(!accessible)
		{
			textColor *= m_inaccessibleTextColorModifier;
			backgroundColor *= m_inaccessibleBackgroundColorModifier;
		}
		textBox.setTextColor(textColor);
		textBox.setBackgroundColor(backgroundColor);

		textBox.setText((*optionIt)->m_name);
		float yOffset = 0.0f;
		if(branchLevel > 0)
			yOffset = static_cast<float>(m_UIMenu->m_branch[branchLevel-1]->m_selection) * 12.0f;
		textBox.setPosition(static_cast<float>(branchLevel)*8.0f*20.0f,static_cast<float>(optionIndex)*12.0f+yOffset);
		m_menuOptionTextBoxes.at(branchLevel).push_back(textBox);
	}
}

void SFMLUIMenu::setMenuListTextBoxColors(UIMenuList* list, int branchLevel, bool accessible)
{
	std::vector<UIMenuOption*>& menuOptions = list->m_options;
	for(std::vector<UIMenuOption*>::iterator optionIt(menuOptions.begin()); optionIt != menuOptions.end(); optionIt++)
	{
		int optionIndex = optionIt - menuOptions.begin();
		sf::Color textColor = m_textColor;
		sf::Color backgroundColor = m_backgroundColor;
		if(list->m_selection == optionIndex)
		{
			textColor = m_selectionTextColor;
			backgroundColor = m_selectionBackgroundColor;
		}
		if(!getMenuOptionAccessible(*optionIt))
		{
			textColor *= m_inaccessibleTextColorModifier;
			backgroundColor *= m_inaccessibleBackgroundColorModifier;
		}
		if(!accessible)
		{
			textColor *= m_inaccessibleTextColorModifier;
			backgroundColor *= m_inaccessibleBackgroundColorModifier;
		}
		m_menuOptionTextBoxes[branchLevel][optionIndex].setTextColor(textColor);
		m_menuOptionTextBoxes[branchLevel][optionIndex].setBackgroundColor(backgroundColor);
	}
}

bool SFMLUIMenu::getMenuOptionAccessible(UIMenuOption* option)
{
	if(option->m_active)
	{
		if(option->m_target)
		{
			if( option->m_target->m_accessible)
			{
				return true;
			}
			return false;
		}
		return true;
	}
	return false;
}

bool SFMLUIMenu::getMenuListOptionAccessible(UIMenuOption* option)
{
	return (option->m_active && (option->m_target && option->m_target->m_accessible));
}