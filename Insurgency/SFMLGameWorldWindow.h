#pragma once
#include "SFML-Template/SFMLGUIElement.h"
#include "GameWorld.h"
#include "SFML-Template/SpriteManager.h"
#include <sstream>
class SFMLGameWorldWindow
	:public SFMLGUIElement
{
public:
	SFMLGameWorldWindow(const sf::Vector2f& lPixelDimentions, const GameWorld& lGameWorld,
		const std::pair<int,int>& lWorldCenter, const std::pair<int,int>& lWorldSize);
	SFMLGameWorldWindow(const GameWorld& lGameWorld, const std::pair<int,int>& lWorldCenter, const std::pair<int,int>& lWorldSize);
	virtual ~SFMLGameWorldWindow(void);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getLocalBounds(void) const;
	virtual sf::FloatRect getGlobalBounds(void) const;
	
	void updateTiles(const std::pair<int,int>& lCenterPos);

private:
	sf::RectangleShape m_rectangle;
	const GameWorld& m_gameWorld;
	sf::IntRect m_worldRect;
	std::vector<std::vector<sf::Sprite>> m_tiles;
};

