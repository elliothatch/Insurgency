#pragma once
#include "SFML-Template/SFMLGUIElement.h"
#include "UIMenu_Creature.h"
#include "SFMLCursesWindow.h"
#include "SFMLCursesTextBox.h"
#include <functional>
//TODO: abstract SFMLUIMenu as a base class
class SFMLUIMenu_Creature : public SFMLGUIElement
{
public:
	SFMLUIMenu_Creature(const sf::Window& window, GameTurnTimer& turnTimer, Creature* creature);
	virtual ~SFMLUIMenu_Creature(void);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getLocalBounds(void) const;
	virtual sf::FloatRect getGlobalBounds(void) const;

	void moveCursorUp();
	void moveCursorDown();
	void selectCursor();
	bool stepBack();

	void updateMenus();

private:
	SFMLCursesWindow m_cursesWindow;
	std::vector<std::vector<SFMLCursesTextBox>> m_menuOptionTextBoxes; //external vector - menuList(branch) - internal vector menuOption
	SFMLCursesTextBox m_helpTextBox;
	UIMenu_Creature m_creatureMenu;
	int m_selection;

	
};

