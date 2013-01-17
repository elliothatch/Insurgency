#include "StdAfx.h"
#include "SFMLCursesChar.h"


SFMLCursesChar::SFMLCursesChar(const sf::Window& window, std::string character)
	:SFMLGUIElement(window),
	 m_character(character),
	 m_backRect(TextureManager::getInstance().getTexture("Rectangle")), 
	 m_charSprite(SpriteManager::getInstance().getSprite(std::string("CursesA_ASCII")+character))
{
	m_backRect.setColor(sf::Color::Black);
	m_charSprite.setColor(sf::Color::White);
}


SFMLCursesChar::SFMLCursesChar(const sf::Window& window, std::string character, const sf::Color& textColor, const sf::Color& backgroundColor)
	:SFMLGUIElement(window),
	 m_character(character),
	 m_backRect(TextureManager::getInstance().getTexture("Rectangle")),
	 m_charSprite(SpriteManager::getInstance().getSprite(std::string("CursesA_ASCII")+character))
{
	m_backRect.setColor(backgroundColor);
	m_charSprite.setColor(textColor);
}


SFMLCursesChar::~SFMLCursesChar(void)
{
}

void SFMLCursesChar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	if(m_backRect.getColor() != sf::Color::Black)
		target.draw(m_backRect, states);
	if(m_character != " ")
		target.draw(m_charSprite, states);
}
sf::FloatRect SFMLCursesChar::getLocalBounds() const
{
	return m_backRect.getLocalBounds();
}
sf::FloatRect SFMLCursesChar::getGlobalBounds() const
{
	return getTransform().transformRect(m_backRect.getGlobalBounds());
}

void SFMLCursesChar::setCharColor(const sf::Color& color)
{
	m_charSprite.setColor(color);
}
void SFMLCursesChar::setBackgroundColor(const sf::Color& color)
{
	m_backRect.setColor(color);
}
void SFMLCursesChar::setCharacter(std::string character)
{
	m_character = character;
	sf::Color charColor = m_charSprite.getColor();
	m_charSprite = sf::Sprite(SpriteManager::getInstance().getSprite(std::string("CursesA_ASCII")+character));
	m_charSprite.setColor(charColor);
}
const sf::Color& SFMLCursesChar::getCharColor() const
{
	return m_charSprite.getColor();
}
const sf::Color& SFMLCursesChar::getBackgroundColor() const
{
	return m_backRect.getColor();
}
std::string SFMLCursesChar::getCharacter() const
{
	return m_character;
}

const sf::Sprite& SFMLCursesChar::getCharSprite() const
{
	return m_charSprite;
}
const sf::Sprite& SFMLCursesChar::getBackRect() const
{
	return m_backRect;
}

std::ostream& operator<<(std::ostream& os, const SFMLCursesChar& cursesChar)
{
	//character char r-g-b-a  back r-g-b-a \n
	sf::Color charColor(cursesChar.getCharColor());
	sf::Color backgroundColor(cursesChar.getBackgroundColor());
	os<<static_cast<int>(cursesChar.m_character.c_str()[0])<<" ";
	os<<static_cast<int>(charColor.r)<<" "<<static_cast<int>(charColor.g)<<
		" "<<static_cast<int>(charColor.b)<<" "<<static_cast<int>(charColor.a)<<" ";
	os<<static_cast<int>(backgroundColor.r)<<" "<<static_cast<int>(backgroundColor.g)<<
		" "<<static_cast<int>(backgroundColor.b)<<" "<<static_cast<int>(backgroundColor.a)<<"\n";
	return os;
}

std::istream& operator>>(std::istream& is, SFMLCursesChar& cursesChar)
{
	if(is.good())
	{
		std::string character = ""; //expressed as a string of an integer (ASCII Value)
		int charR, charG, charB, charA, backR, backG, backB, backA = 0;
		is>>character;
		is>>charR>>charG>>charB>>charA;
		is>>backR>>backG>>backB>>backA;
		char c[2] = {static_cast<char>(std::atoi(character.c_str())), '\0'}; //convert multi-char integer string into one char value
		cursesChar.setCharacter(std::string(c));
		cursesChar.setCharColor(sf::Color(
			static_cast<sf::Uint8>(charR),static_cast<sf::Uint8>(charG),static_cast<sf::Uint8>(charB),static_cast<sf::Uint8>(charA)));
		cursesChar.setBackgroundColor(sf::Color(
			static_cast<sf::Uint8>(backR),static_cast<sf::Uint8>(backG),static_cast<sf::Uint8>(backB),static_cast<sf::Uint8>(backA)));
	}
	return is;
}