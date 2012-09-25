#include "StdAfx.h"
#include "SFMLCursesMenu.h"


SFMLCursesMenu::SFMLCursesMenu(const sf::Vector2i& lCharSize)
	:m_cursesWindow(lCharSize),
	m_isActive(false), m_keyboardCursorPos(0), m_mouseCursorPos(0),
	m_menuItemCount(lCharSize.x),
	m_textColor(sf::Color::White), m_textKeyboardHighlightColor(sf::Color::Red), m_textMouseHighlightColor(sf::Color::Blue),
	m_emptyString("Empty")
{
	if(lCharSize.x == 0)
	{
		m_cursesWindow.setCursesSize(sf::Vector2i(1,lCharSize.y));
		setLineText(m_emptyString, 0);
		m_menuItemCount = 0;
	}
	setMouseRolloverFunction(std::make_shared<TFunctor<SFMLCursesMenu>>(this, &SFMLCursesMenu::OnRollover));
	setMouseLeftClickedFunction(std::make_shared<TFunctor<SFMLCursesMenu>>(this, &SFMLCursesMenu::selectMouseCursor));
}

SFMLCursesMenu::SFMLCursesMenu(const sf::Vector2i& lCharSize, const std::string& lEmptyString)
	:m_cursesWindow(lCharSize),
	m_isActive(false), m_keyboardCursorPos(0), m_mouseCursorPos(0),
	m_menuItemCount(lCharSize.x),
	m_textColor(sf::Color::White), m_textKeyboardHighlightColor(sf::Color::Red), m_textMouseHighlightColor(sf::Color::Blue),
	m_emptyString(lEmptyString)
{
	if(lCharSize.x == 0)
	{
		m_cursesWindow.setCursesSize(sf::Vector2i(1,lCharSize.y));
		setLineText(m_emptyString, 0);
		m_menuItemCount = 0;
	}
	setMouseRolloverFunction(std::make_shared<TFunctor<SFMLCursesMenu>>(this, &SFMLCursesMenu::OnRollover));
	setMouseLeftClickedFunction(std::make_shared<TFunctor<SFMLCursesMenu>>(this, &SFMLCursesMenu::selectMouseCursor));
}

SFMLCursesMenu::~SFMLCursesMenu(void)
{
}


void SFMLCursesMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_cursesWindow, states);
}

sf::FloatRect SFMLCursesMenu::getLocalBounds(void) const
{
	return m_cursesWindow.getLocalBounds();
}
sf::FloatRect SFMLCursesMenu::getGlobalBounds(void) const
{
	return getTransform().transformRect(m_cursesWindow.getGlobalBounds());
}

void SFMLCursesMenu::moveKeyboardCursorToPosition(int position)
{
	if(m_menuItemCount == 0)
		return;

	//reset old colors
	for(int i = 0; i < m_cursesWindow.getCursesSize().y; i++)
	{
		sf::Vector2i windowPos(m_keyboardCursorPos, i);
		sf::Sprite sprite(m_cursesWindow.getTileSprite(windowPos));
		sprite.setColor(m_textColor);
		m_cursesWindow.setTileSprite(sprite,windowPos);
	}
	//set new colors
	m_keyboardCursorPos = position;
	for(int i = 0; i < m_cursesWindow.getCursesSize().y; i++)
	{
		sf::Vector2i windowPos(m_keyboardCursorPos, i);
		sf::Sprite sprite(m_cursesWindow.getTileSprite(windowPos));
		sprite.setColor(m_textKeyboardHighlightColor);
		m_cursesWindow.setTileSprite(sprite,windowPos);
	}
}
void SFMLCursesMenu::moveKeyboardCursorUp()
{
	if(m_keyboardCursorPos == 0)
		moveKeyboardCursorToPosition(m_menuItemCount - 1);
	else
		moveKeyboardCursorToPosition(m_keyboardCursorPos - 1);
}
void SFMLCursesMenu::moveKeyboardCursorDown()
{
	if(m_keyboardCursorPos == m_menuItemCount - 1)
		moveKeyboardCursorToPosition(0);
	else
		moveKeyboardCursorToPosition(m_keyboardCursorPos + 1);
	
}
void SFMLCursesMenu::setMouseCursor()
{
	if(m_menuItemCount == 0)
		return;

	sf::Vector2f pos = getPosition();
	int localMouseY = m_mouseY - static_cast<int>(pos.y);

	//reset old colors
	for(int i = 0; i < m_cursesWindow.getCursesSize().y; i++)
	{
		sf::Vector2i windowPos(m_mouseCursorPos, i);
		sf::Sprite sprite(m_cursesWindow.getTileSprite(windowPos));
		if(m_mouseCursorPos == m_keyboardCursorPos)
			sprite.setColor(m_textKeyboardHighlightColor);
		else
			sprite.setColor(m_textColor);
		m_cursesWindow.setTileSprite(sprite,windowPos);
	}
	//set new colors
	m_mouseCursorPos = localMouseY/12; //12 == curses char height
	for(int i = 0; i < m_cursesWindow.getCursesSize().y; i++)
	{
		sf::Vector2i windowPos(m_mouseCursorPos, i);
		sf::Sprite sprite(m_cursesWindow.getTileSprite(windowPos));
		sprite.setColor(m_textMouseHighlightColor);
		m_cursesWindow.setTileSprite(sprite,windowPos);
	}
}

void SFMLCursesMenu::OnRollover()
{
	if(!m_isActive)
		return;
	setMouseCursor();
}

void SFMLCursesMenu::selectKeyboardCursor()
{
	if(m_menuItemCount)
		doActionAtIndex(m_keyboardCursorPos);
}
void SFMLCursesMenu::selectMouseCursor()
{
	if(m_menuItemCount)
	{
		setMouseCursor();
		doActionAtIndex(m_mouseCursorPos);
	}
}

void SFMLCursesMenu::setLineText(const std::string& lString, unsigned int position)
{
	for(int i = 0; i < m_cursesWindow.getCursesSize().y; i++)
	{
		if(i == lString.size())
			break;
		sf::Vector2i windowPos(position, i);
		sf::Sprite sprite(SpriteManager::getInstance().getSprite(std::string("CursesA_ASCII") + lString.at(i)));
		sprite.setColor(m_textColor);
		m_cursesWindow.setTileSprite(sprite,windowPos);
	}
}

void SFMLCursesMenu::setIsActive(bool b)
{
	m_isActive = b;
	if(!b)
		resetTextColor();
}
bool SFMLCursesMenu::getIsActive() const
{
	return m_isActive;
}
void SFMLCursesMenu::resetTextColor()
{
	for(int i = 0; i < m_cursesWindow.getCursesSize().y; i++)
	{
		sf::Vector2i windowPos(m_mouseCursorPos, i);
		sf::Sprite sprite(m_cursesWindow.getTileSprite(windowPos));
		sprite.setColor(m_textColor);
		m_cursesWindow.setTileSprite(sprite,windowPos);
	}
	for(int i = 0; i < m_cursesWindow.getCursesSize().y; i++)
	{
		sf::Vector2i windowPos(m_keyboardCursorPos, i);
		sf::Sprite sprite(m_cursesWindow.getTileSprite(windowPos));
		sprite.setColor(m_textColor);
		m_cursesWindow.setTileSprite(sprite,windowPos);
	}
}
