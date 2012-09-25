#pragma once
#include "SFML-Template/SFMLGUIElement.h"
#include "SFMLCursesWindow.h"
class SFMLCursesMenu :
	public SFMLGUIElement
{
public:
	SFMLCursesMenu(const sf::Vector2i& lCharSize);
	SFMLCursesMenu(const sf::Vector2i& lCharSize, const std::string& lEmptyString);
	virtual ~SFMLCursesMenu(void);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getLocalBounds(void) const;
	virtual sf::FloatRect getGlobalBounds(void) const;

	void moveKeyboardCursorToPosition(int position);
	void moveKeyboardCursorUp();
	void moveKeyboardCursorDown();

	void setMouseCursor();

	void selectKeyboardCursor();
	void selectMouseCursor();
	void OnRollover();

	virtual void doActionAtIndex(unsigned int position) = 0;

	void setLineText(const std::string& lString, unsigned int position);

	void setIsActive(bool b);
	bool getIsActive() const;

	void resetTextColor();

protected:
	bool m_isActive;
	unsigned int m_keyboardCursorPos;
	int m_mouseCursorPos;
	unsigned int m_menuItemCount;
	SFMLCursesWindow m_cursesWindow;
	sf::Color m_textColor;
	sf::Color m_textKeyboardHighlightColor;
	sf::Color m_textMouseHighlightColor;
	std::string m_emptyString;
};

