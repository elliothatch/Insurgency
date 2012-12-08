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
	 m_inaccessibleTextColorModifier(200,200,200,255),
	 m_inaccessibleBackgroundColorModifier(200,200,200,255)
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
	if(!m_UIMenu->m_currentMenuList->m_options[m_selection]->m_active || (m_UIMenu->m_nextMenuList && !m_UIMenu->m_nextMenuList->m_accessible))
	{
		textColor *= m_inaccessibleTextColorModifier;
		backgroundColor *= m_inaccessibleBackgroundColorModifier;
	}
	m_menuOptionTextBoxes[m_branchLevel][m_selection].setTextColor(textColor);
	m_menuOptionTextBoxes[m_branchLevel][m_selection].setBackgroundColor(backgroundColor);

	m_selection = s;
	m_UIMenu->select(m_selection);
	
	//reuse color variables
	textColor = m_selectionTextColor;
	backgroundColor = m_selectionBackgroundColor;
	if(!m_UIMenu->m_currentMenuList->m_options[m_selection]->m_active || (m_UIMenu->m_nextMenuList && !m_UIMenu->m_nextMenuList->m_accessible))
	{
		textColor *= m_inaccessibleTextColorModifier;
		backgroundColor *= m_inaccessibleBackgroundColorModifier;
	}

	m_menuOptionTextBoxes[m_branchLevel][m_selection].setTextColor(textColor);
	m_menuOptionTextBoxes[m_branchLevel][m_selection].setBackgroundColor(backgroundColor);

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
	if(m_selection ==  m_UIMenu->m_currentMenuList->m_options.size() - 1 || m_UIMenu->m_currentMenuList->m_options.size() == 1)
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
		addMenuListTextBox(m_UIMenu->m_branch[m_branchLevel], m_branchLevel);
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
		m_UIMenu->stepLeft();
		m_selection = m_UIMenu->m_currentMenuList->m_selection;
		m_branchLevel = m_UIMenu->m_branch.size()-1;
		m_helpTextBox.setText(m_UIMenu->m_helpText);
		m_menuOptionTextBoxes.pop_back();
		return true;
	}
	return false;
}

void SFMLUIMenu::updateMenus()
{
	m_menuOptionTextBoxes.clear();
	for(std::vector<UIMenuList*>::iterator listIt(m_UIMenu->m_branch.begin()); listIt != m_UIMenu->m_branch.end(); listIt++)
	{
		int listIndex = listIt-m_UIMenu->m_branch.begin();	
		addMenuListTextBox(*listIt, listIndex);
	}
	m_helpTextBox.setText(m_UIMenu->m_helpText);
}

void SFMLUIMenu::addMenuListTextBox(UIMenuList* list, int branchLevel)
{
	m_menuOptionTextBoxes.push_back(std::vector<SFMLCursesTextBox>());
	std::vector<UIMenuOption*>& menuOptions = list->m_options;
	for(std::vector<UIMenuOption*>::iterator optionIt(menuOptions.begin()); optionIt != menuOptions.end(); optionIt++)
	{
		int optionIndex = optionIt - menuOptions.begin();
		SFMLCursesTextBox textBox(m_window, sf::Vector2i(1,20));
		if(list->m_selection == optionIndex)
		{
			textBox.setTextColor(m_selectionTextColor);
			textBox.setBackgroundColor(m_selectionBackgroundColor);
		}
		else
		{
			textBox.setTextColor(m_textColor);
			textBox.setBackgroundColor(m_backgroundColor);
		}
		if(!(*optionIt)->m_active || ((*optionIt)->m_target && !(*optionIt)->m_target->m_accessible))
		{
			textBox.setTextColor(textBox.getTextColor()*m_inaccessibleTextColorModifier);
			textBox.setBackgroundColor(textBox.getBackgroundColor()*m_inaccessibleBackgroundColorModifier);
		}
		textBox.setText((*optionIt)->m_name);
		textBox.setPosition(static_cast<float>(branchLevel)*8.0f*20.0f,static_cast<float>(optionIndex)*12.0f);
		m_menuOptionTextBoxes.at(branchLevel).push_back(textBox);
	}
}