#pragma once
#include "SFMLUIMenu.h"
#include "UIMenu_Creature.h"
#include "SFMLCursesWindow.h"
#include "SFMLCursesTextBox.h"
//TODO: abstract SFMLUIMenu as a base class
class SFMLUIMenu_Creature : public SFMLUIMenu
{
public:
	SFMLUIMenu_Creature(const sf::Window& window, GameTurnTimer& turnTimer, Creature* creature);
	virtual ~SFMLUIMenu_Creature(void);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getLocalBounds(void) const;
	virtual sf::FloatRect getGlobalBounds(void) const;

private:
	sf::RectangleShape m_rectangle;
	
};

