#pragma once
#include <SFML/Graphics.hpp>
#include "SFMLGUIElement.h"
//a more specific GUIElement, acts like a button, not just a clickable sprite
class SFMLButton :
	public SFMLGUIElement
{
public:
	SFMLButton(const sf::Window& window);
	SFMLButton(const sf::Window& window, sf::Sprite unpressedSprite);
	SFMLButton(const sf::Window& window, sf::Sprite unpressedSprite, sf::Sprite pressedSprite);
	virtual ~SFMLButton(void);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getLocalBounds(void) const;
	virtual sf::FloatRect getGlobalBounds(void) const;

	void setUnpressedSprite(sf::Sprite sprite);
	void setPressedSprite(sf::Sprite sprite);
	sf::Sprite& getUnpressedSprite(void) const;
	sf::Sprite& getPressedSprite(void) const;

protected:
	sf::Sprite m_unpressedSprite;
	sf::Sprite m_pressedSprite;
};

