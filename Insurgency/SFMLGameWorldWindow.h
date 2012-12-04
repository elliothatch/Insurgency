#pragma once
#include "SFML-Template/SFMLGUIElement.h"
#include "GameWorld.h"
#include "SFMLCursesCharManager.h"
#include "SFMLCursesWindow.h"
class SFMLGameWorldWindow
	:public SFMLGUIElement
{
public:
	SFMLGameWorldWindow(const sf::Window& window, const GameWorld& lGameWorld, 
		const std::pair<int,int>& lWorldCenter, const std::pair<int,int>& lWorldSize);
	virtual ~SFMLGameWorldWindow(void);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getLocalBounds(void) const;
	virtual sf::FloatRect getGlobalBounds(void) const;
	
	void updateTiles(const std::pair<int,int>& lCenterPos);

private:
	SFMLCursesWindow m_cursesWindow;
	const GameWorld& m_gameWorld;
	sf::IntRect m_worldRect;
};

