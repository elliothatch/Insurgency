#pragma once
#include "SFML-Template/SFMLGUIElement.h"
#include "GameWorld.h"
#include "SFML-Template/SpriteManager.h"
#include <string>
#include <sstream>
#include "SFMLCursesWindow.h"
class SFMLWorldItemsWindow
	:public SFMLGUIElement
{
public:
	SFMLWorldItemsWindow(const sf::Vector2i& lCharSize, const GameWorld& lGameWorld, std::pair<int,int> lWorldPoint);
	virtual ~SFMLWorldItemsWindow(void);
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getLocalBounds(void) const;
	virtual sf::FloatRect getGlobalBounds(void) const;

	void update(std::pair<int,int> lWorldPoint);

private:
	SFMLCursesWindow m_cursesWindow;
	const GameWorld& m_gameWorld;
	std::pair<int,int> m_worldPoint;
};

