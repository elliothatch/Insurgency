#include "StdAfx.h"
#include "SFMLCursesWindow.h"


SFMLCursesWindow::SFMLCursesWindow(const sf::Window& window, const sf::Vector2i& lCursesSize)
	:SFMLGUIElement(window),
	 m_rectangle(sf::Vector2f(static_cast<float>(lCursesSize.y)*8.0f, static_cast<float>(lCursesSize.x)*12.0f)),
	 m_tiles(),
	 m_cursesSize(0,0)
{
	setCursesSize(lCursesSize);
	m_rectangle.setFillColor(sf::Color::Black);
}

void SFMLCursesWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_rectangle, states);
	for(std::vector<std::vector<SFMLCursesChar>>::const_iterator xIt(m_tiles.begin()); xIt != m_tiles.end(); xIt++)
	{
		for(std::vector<SFMLCursesChar>::const_iterator yIt(xIt->begin()); yIt != xIt->end(); yIt++)
		{
			target.draw(*yIt, states);
		}
	}
}
sf::FloatRect SFMLCursesWindow::getLocalBounds(void) const
{
	return m_rectangle.getLocalBounds();
}
sf::FloatRect SFMLCursesWindow::getGlobalBounds(void) const
{
	return getTransform().transformRect(m_rectangle.getGlobalBounds());
}

void SFMLCursesWindow::clearTiles()
{
	for(int i = 0; i < m_cursesSize.x; i++)
	{
		for(int j = 0; j < m_cursesSize.y; j++)
		{
			setTile(SFMLCursesChar(m_window, " "), sf::Vector2i(i,j));
		}
	}
}
void SFMLCursesWindow::clearTiles(std::string character, const sf::Color& textColor, const sf::Color& backgroundColor)
{
	for(int i = 0; i < m_cursesSize.x; i++)
	{
		for(int j = 0; j < m_cursesSize.y; j++)
		{
			setTile(SFMLCursesChar(m_window, character, textColor, backgroundColor), sf::Vector2i(i,j));
		}
	}
}
void SFMLCursesWindow::setBorder(const SFMLCursesChar& borderChar)
{
	setBorder(borderChar,borderChar,borderChar,borderChar,borderChar,borderChar,borderChar,borderChar);
}
void SFMLCursesWindow::setBorder(const SFMLCursesChar& top, const SFMLCursesChar& bottom, const SFMLCursesChar& left, const SFMLCursesChar& right, 
		const SFMLCursesChar& topLeftCorner, const SFMLCursesChar& topRightCorner, 
		const SFMLCursesChar& bottomRightCorner, const SFMLCursesChar& bottomLeftCorner)
{
	setTile(topLeftCorner, sf::Vector2i(0,0));
	for(int i = 1; i<m_cursesSize.y-1; i++)
	{
		setTile(top,sf::Vector2i(0,i));
	}
	setTile(topRightCorner, sf::Vector2i(0,m_cursesSize.y-1));
	for(int i = 1; i<m_cursesSize.x-1; i++)
	{
		setTile(right,sf::Vector2i(i,m_cursesSize.y-1));
	}
	setTile(bottomRightCorner,sf::Vector2i(m_cursesSize.x-1,m_cursesSize.y-1));
	for(int i = 1; i<m_cursesSize.y-1; i++)
	{
		setTile(bottom,sf::Vector2i(m_cursesSize.x-1,i));
	}
	setTile(bottomLeftCorner, sf::Vector2i(m_cursesSize.x-1,0));
	for(int i = 1; i<m_cursesSize.x-1; i++)
	{
		setTile(left,sf::Vector2i(i,0));
	}
}
void SFMLCursesWindow::setTile(const SFMLCursesChar& cursesChar, const sf::Vector2i& tilePos)
{
	m_tiles.at(tilePos.x).at(tilePos.y) = cursesChar;
	m_tiles.at(tilePos.x).at(tilePos.y).setPosition(static_cast<float>(tilePos.y)*8.0f, static_cast<float>(tilePos.x)*12.0f);
}
void SFMLCursesWindow::setTiles(const std::string& text, const sf::Color& textColor, const sf::Color& backColor, const sf::Vector2i& tilePos)
{
	for(std::string::const_iterator stringIt(text.begin()); stringIt != text.end(); stringIt++)
	{
		unsigned int stringPos = stringIt - text.begin();

		sf::Vector2i charPos(tilePos.x+((tilePos.y+stringPos)/m_cursesSize.y), (tilePos.y + stringPos)%m_cursesSize.y);
		if(charPos.x >= m_cursesSize.x || charPos.y >= m_cursesSize.y)
			break;
		setTile(SFMLCursesChar(m_window,std::string("")+*stringIt,textColor,backColor),charPos);
	}
}
const SFMLCursesChar& SFMLCursesWindow::getTile(const sf::Vector2i& lTilePos) const
{
	return m_tiles.at(lTilePos.x).at(lTilePos.y);
}

void SFMLCursesWindow::setCursesSize(const sf::Vector2i& lCursesSize)
{	
	m_tiles.resize(lCursesSize.x);
	for(std::vector<std::vector<SFMLCursesChar>>::iterator yIt(m_tiles.begin()); yIt != m_tiles.end(); yIt++)
	{
		const int yIndex = yIt - m_tiles.begin();
		yIt->resize(lCursesSize.y, SFMLCursesChar(m_window, " "));
		for(std::vector<SFMLCursesChar>::iterator xIt(yIt->begin()); xIt != yIt->end(); xIt++)
		{
			const int xIndex = xIt - yIt->begin();
			xIt->setPosition(static_cast<float>(xIndex)*8.0f, static_cast<float>(yIndex)*12.0f);
		}
	}
	m_cursesSize = lCursesSize;
	m_rectangle.setSize(sf::Vector2f(lCursesSize.y*8.0f, lCursesSize.x*12.0f));
}

sf::Vector2i SFMLCursesWindow::getCursesSize() const
{
	return m_cursesSize;
}

std::ostream& operator<<(std::ostream& os, const SFMLCursesWindow& cursesWindow)
{
	os<<cursesWindow.m_cursesSize.x<<" "<<cursesWindow.m_cursesSize.y<<"\n";
	for(int i = 0; i<cursesWindow.m_cursesSize.x; i++) //lines
	{
		for(int j = 0; j<cursesWindow.m_cursesSize.y; j++) //columns
		{
			os<<cursesWindow.m_tiles.at(i).at(j);
		}
	}
	return os;
}

std::istream& operator>>(std::istream& is, SFMLCursesWindow& cursesWindow)
{
	sf::Vector2i cursesSize;
	is>>cursesSize.x>>cursesSize.y;
	cursesWindow.setCursesSize(cursesSize);
	for(int i = 0; i<cursesSize.x; i++) //lines
	{
		for(int j = 0; j<cursesSize.y; j++) //columns
		{
			if(is.good())
			{
				SFMLCursesChar cursesChar(cursesWindow.m_window, " ");
				is>>cursesChar;
				cursesWindow.setTile(cursesChar, sf::Vector2i(i,j));
			}
		}
	}
	return is;
}