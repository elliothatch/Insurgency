#include "StdAfx.h"
#include "SFMLUIMenu_Creature.h"


SFMLUIMenu_Creature::SFMLUIMenu_Creature(const sf::Window& window, GameTurnTimer& turnTimer, Creature* creature)
	:SFMLGUIElement(window),
	 m_cursesWindow(m_window,sf::Vector2i(20,20)),
	 m_helpTextBox(m_window, sf::Vector2i(10,30)),
	 m_creatureMenu(turnTimer, *creature),
	 m_selection(0)
{
	m_cursesWindow.clearTiles(".",sf::Color::White,sf::Color::Black);

	m_helpTextBox.setPosition(0,300);
	m_helpTextBox.setText(m_creatureMenu.m_helpText);
	//m_creatureMenu.select(0); //inventory
	//m_creatureMenu.stepRight();
	//m_creatureMenu.stepRight();//ak
	//m_creatureMenu.stepRight();//drop
	//m_helpTextBox.setText(m_creatureMenu.m_currentMenuList->m_options.at(0)->m_helpText);
	updateMenus();
}


SFMLUIMenu_Creature::~SFMLUIMenu_Creature(void)
{
}

void SFMLUIMenu_Creature::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_cursesWindow, states);
	for(std::vector<std::vector<SFMLCursesTextBox>>::const_iterator vecIt(m_menuOptionTextBoxes.begin()); vecIt != m_menuOptionTextBoxes.end(); vecIt++)
	{
		for(std::vector<SFMLCursesTextBox>::const_iterator boxIt(vecIt->begin()); boxIt != vecIt->end(); boxIt++)
		{
			target.draw(*boxIt, states);
		}
	}
	target.draw(m_helpTextBox, states);
}
sf::FloatRect SFMLUIMenu_Creature::getLocalBounds(void) const
{
	return m_cursesWindow.getLocalBounds();
}
sf::FloatRect SFMLUIMenu_Creature::getGlobalBounds(void) const
{
	return getTransform().transformRect(m_cursesWindow.getGlobalBounds());
}

void SFMLUIMenu_Creature::moveCursorUp()
{
	m_menuOptionTextBoxes[m_creatureMenu.m_branch.size()-1][m_selection].setTextColor(sf::Color::White);
	m_menuOptionTextBoxes[m_creatureMenu.m_branch.size()-1][m_selection].setBackgroundColor(sf::Color::Black);

	if(m_selection == 0 || m_creatureMenu.m_currentMenuList->m_options.size() == 1)
		m_selection = m_creatureMenu.m_currentMenuList->m_options.size() - 1;
	else
		m_selection--;
	m_creatureMenu.select(m_selection);
	m_menuOptionTextBoxes[m_creatureMenu.m_branch.size()-1][m_selection].setTextColor(sf::Color::Black);
	m_menuOptionTextBoxes[m_creatureMenu.m_branch.size()-1][m_selection].setBackgroundColor(sf::Color::White);
}
void SFMLUIMenu_Creature::moveCursorDown()
{
	m_menuOptionTextBoxes[m_creatureMenu.m_branch.size()-1][m_selection].setTextColor(sf::Color::White);
	m_menuOptionTextBoxes[m_creatureMenu.m_branch.size()-1][m_selection].setBackgroundColor(sf::Color::Black);
	if(m_selection ==  m_creatureMenu.m_currentMenuList->m_options.size() - 1 || m_creatureMenu.m_currentMenuList->m_options.size() == 1)
		m_selection = 0;
	else
		m_selection++;
	m_creatureMenu.select(m_selection);
	m_menuOptionTextBoxes[m_creatureMenu.m_branch.size()-1][m_selection].setTextColor(sf::Color::Black);
	m_menuOptionTextBoxes[m_creatureMenu.m_branch.size()-1][m_selection].setBackgroundColor(sf::Color::White);
	
}
void SFMLUIMenu_Creature::selectCursor()
{
	m_creatureMenu.stepRight();
	m_selection = m_creatureMenu.m_currentMenuList->m_selection;
	//TODO: add code for when OnExecute is called
	updateMenus();
}
bool SFMLUIMenu_Creature::stepBack()
{
	if(m_creatureMenu.m_previousMenuList)
	{
		m_creatureMenu.stepLeft();
		m_selection = m_creatureMenu.m_currentMenuList->m_selection;
		updateMenus();
		return true;
	}
	return false;
}

void SFMLUIMenu_Creature::updateMenus()
{
	m_menuOptionTextBoxes.clear();
	for(std::vector<UIMenuList*>::iterator listIt(m_creatureMenu.m_branch.begin()); listIt != m_creatureMenu.m_branch.end(); listIt++)
	{
		int listIndex = listIt-m_creatureMenu.m_branch.begin();	
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
	//m_menuOptionTextBoxes[m_selection].setTextColor(sf::Color::Red);
}