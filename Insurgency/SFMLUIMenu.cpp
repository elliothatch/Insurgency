#include "StdAfx.h"
#include "SFMLUIMenu.h"


SFMLUIMenu::SFMLUIMenu(const sf::Window& window)
	:SFMLGUIElement(window),
	 m_helpTextBox(m_window, sf::Vector2i(10,30)),
	 m_UIMenu(nullptr),
	 m_selection(0),
	 m_branchLevel(0),
	 m_selectionTextColor(sf::Color::Black),
	 m_selectionBackgroundColor(sf::Color::White)
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
	m_menuOptionTextBoxes[m_branchLevel][m_selection].setTextColor(sf::Color::White);
	m_menuOptionTextBoxes[m_branchLevel][m_selection].setBackgroundColor(sf::Color::Black);
	m_selection = s;
	m_UIMenu->select(m_selection);
	
	m_menuOptionTextBoxes[m_branchLevel][m_selection].setTextColor(m_selectionTextColor);
	m_menuOptionTextBoxes[m_branchLevel][m_selection].setBackgroundColor(m_selectionBackgroundColor);

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
		//only update the new menu if you can
		std::vector<UIMenuOption*>& menuOptions = m_UIMenu->m_branch[m_branchLevel]->m_options;
		m_menuOptionTextBoxes.push_back(std::vector<SFMLCursesTextBox>());
		for(std::vector<UIMenuOption*>::iterator optionIt(menuOptions.begin()); optionIt != menuOptions.end(); optionIt++)
		{
			int optionIndex = optionIt - menuOptions.begin();
			SFMLCursesTextBox textBox(m_window, sf::Vector2i(1,20));
			if( m_UIMenu->m_branch[m_branchLevel]->m_selection == optionIndex)
			{
				textBox.setTextColor(sf::Color::Black);
				textBox.setBackgroundColor(sf::Color::White);
			}
			textBox.setText((*optionIt)->m_name);
			textBox.setPosition(static_cast<float>(m_branchLevel)*8.0f*20.0f,static_cast<float>(optionIndex)*12.0f);
			m_menuOptionTextBoxes.at(m_branchLevel).push_back(textBox);
		
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
		std::vector<UIMenuOption*>& menuOptions = (*listIt)->m_options;
		m_menuOptionTextBoxes.push_back(std::vector<SFMLCursesTextBox>());
		for(std::vector<UIMenuOption*>::iterator optionIt(menuOptions.begin()); optionIt != menuOptions.end(); optionIt++)
		{
			int optionIndex = optionIt - menuOptions.begin();
			SFMLCursesTextBox textBox(m_window, sf::Vector2i(1,20));
			if((*listIt)->m_selection == optionIndex)
			{
				textBox.setTextColor(sf::Color::Black);
				textBox.setBackgroundColor(sf::Color::White);
			}
			textBox.setText((*optionIt)->m_name);
			textBox.setPosition(static_cast<float>(listIndex)*8.0f*20.0f,static_cast<float>(optionIndex)*12.0f);
			m_menuOptionTextBoxes.at(listIndex).push_back(textBox);
		
		}
	}
	m_helpTextBox.setText(m_UIMenu->m_helpText);
}