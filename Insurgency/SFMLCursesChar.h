#pragma once
#include "SFML-Template/SFMLGUIElement.h"
#include "SFML-Template/SpriteManager.h"
#include <sstream>
class SFMLCursesChar : public SFMLGUIElement
{
public:
	SFMLCursesChar(const sf::Window& window, std::string character);
	SFMLCursesChar(const sf::Window& window, std::string character, const sf::Color& textColor, const sf::Color& backgroundColor);
	~SFMLCursesChar(void);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getLocalBounds() const;
	virtual sf::FloatRect getGlobalBounds() const;

	void setCharColor(const sf::Color& color);
	void setBackgroundColor(const sf::Color& color);
	void setCharacter(std::string character);

	const sf::Color& getCharColor() const;
	const sf::Color& getBackgroundColor() const;
	std::string getCharacter() const;

	const sf::Sprite& getCharSprite() const;
	const sf::Sprite& getBackRect() const;

	friend std::ostream& operator<<(std::ostream& os, const SFMLCursesChar& cursesChar);
	friend std::istream& operator>>(std::istream& is, SFMLCursesChar& cursesChar);

protected:
	std::string m_character;
	sf::Sprite m_backRect;
	sf::Sprite m_charSprite;
};

std::ostream& operator<<(std::ostream& os, const SFMLCursesChar& cursesChar);
std::istream& operator>>(std::istream& is, SFMLCursesChar& cursesChar);
