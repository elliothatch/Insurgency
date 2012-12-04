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
	//m_creatureMenu.select(0); //ak
	//m_creatureMenu.stepRight();
	//m_creatureMenu.select(0); //drop
	//m_creatureMenu.stepRight();
	//m_helpTextBox.setText(m_creatureMenu.m_currentMenuList->m_options.at(0)->m_helpText);
	std::vector<UIMenuOption*>& menuOptions = m_creatureMenu.m_currentMenuList->m_options;
	for(std::vector<UIMenuOption*>::iterator optionIt(menuOptions.begin()); optionIt != menuOptions.end(); optionIt++)
	{
		SFMLCursesTextBox textBox(m_window, sf::Vector2i(1,30));
		textBox.setText((*optionIt)->m_name);
		textBox.setPosition(0,(optionIt - menuOptions.begin())*12.0f);
		m_menuOptionTextBoxes.push_back(textBox);
		
	}
}


SFMLUIMenu_Creature::~SFMLUIMenu_Creature(void)
{
}

void SFMLUIMenu_Creature::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_cursesWindow, states);
	for(std::vector<SFMLCursesTextBox>::const_iterator boxIt(m_menuOptionTextBoxes.begin()); boxIt != m_menuOptionTextBoxes.end(); boxIt++)
	{
		target.draw(*boxIt, states);
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
	m_menuOptionTextBoxes[m_selection].setTextColor(sf::Color::White);

	if(m_selection == 0)
		m_selection = m_creatureMenu.m_currentMenuList->m_options.size() - 1;
	else
		m_selection--;
	m_creatureMenu.select(m_selection);
	m_menuOptionTextBoxes[m_selection].setTextColor(sf::Color::Red);
}
void SFMLUIMenu_Creature::moveCursorDown()
{
	m_menuOptionTextBoxes[m_selection].setTextColor(sf::Color::White);
	if(m_selection ==  m_creatureMenu.m_currentMenuList->m_options.size() - 1)
		m_selection = 0;
	else
		m_selection++;
	m_creatureMenu.select(m_selection);
	m_menuOptionTextBoxes[m_selection].setTextColor(sf::Color::Red);
	
}
void SFMLUIMenu_Creature::selectCursor()
{
	m_creatureMenu.stepRight();
	//TODO: add code for when OnExecute is called
	updateMenus();
}

void SFMLUIMenu_Creature::updateMenus()
{
	m_menuOptionTextBoxes.clear();
	std::vector<UIMenuOption*>& menuOptions = m_creatureMenu.m_currentMenuList->m_options;
	for(std::vector<UIMenuOption*>::iterator optionIt(menuOptions.begin()); optionIt != menuOptions.end(); optionIt++)
	{
		SFMLCursesTextBox textBox(m_window, sf::Vector2i(1,30));
		textBox.setText((*optionIt)->m_name);
		textBox.setPosition(0,(optionIt - menuOptions.begin())*12.0f);
		m_menuOptionTextBoxes.push_back(textBox);
		
	}
}