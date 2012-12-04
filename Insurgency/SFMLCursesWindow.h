#pragma once
#include "SFML-Template/SFMLGUIElement.h"
#include "SFML-Template/SpriteManager.h"
#include "SFMLCursesChar.h"
#include <fstream>
class SFMLCursesWindow
	:public SFMLGUIElement
{
public:
	SFMLCursesWindow(const sf::Window& window, const sf::Vector2i& lCursesSize);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getLocalBounds(void) const;
	virtual sf::FloatRect getGlobalBounds(void) const;

	void clearTiles();
	void clearTiles(std::string character, const sf::Color& textColor, const sf::Color& backgroundColor);
	void setTile(const SFMLCursesChar& cursesChar, const sf::Vector2i& tilePos);
	void setBorder(const SFMLCursesChar& borderChar);
	void setBorder(const SFMLCursesChar& top, const SFMLCursesChar& bottom, const SFMLCursesChar& left, const SFMLCursesChar& right, 
		const SFMLCursesChar& topLeftCorner, const SFMLCursesChar& topRightCorner, 
		const SFMLCursesChar& bottomRightCorner, const SFMLCursesChar& bottomLeftCorner);
	void setTiles(const std::string& text, const sf::Color& textColor, const sf::Color& backColor, const sf::Vector2i& tilePos);

	const SFMLCursesChar& getTile(const sf::Vector2i& lTilePos) const;

	void setCursesSize(const sf::Vector2i& lCursesSize);
	sf::Vector2i getCursesSize() const;

	friend std::ostream& operator<<(std::ostream& os, const SFMLCursesWindow& cursesWindow);
	friend std::istream& operator>>(std::istream& is, SFMLCursesWindow& cursesWindow);

protected:
	sf::RectangleShape m_rectangle;
	std::vector<std::vector<SFMLCursesChar>> m_tiles; //[lines, columns]
	sf::Vector2i m_cursesSize;
};

std::ostream& operator<<(std::ostream& os, const SFMLCursesWindow& cursesWindow);
std::istream& operator>>(std::istream& is, SFMLCursesWindow& cursesWindow);