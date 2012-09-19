#include "StdAfx.h"
#include "SFMLCursesWindow.h"


SFMLCursesWindow::SFMLCursesWindow(const sf::Vector2i& lCursesSize)
	:m_rectangle(sf::Vector2f(static_cast<float>(lCursesSize.x)*8.0f, static_cast<float>(lCursesSize.y)*12.0f)),
	 m_tiles(),
	 m_cursesSize(0,0)
{
	setCursesSize(lCursesSize);
}


SFMLCursesWindow::~SFMLCursesWindow(void)
{
}


void SFMLCursesWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	for(std::vector<std::vector<sf::Sprite>>::const_iterator xIt(m_tiles.begin()); xIt != m_tiles.end(); xIt++)
	{
		for(std::vector<sf::Sprite>::const_iterator yIt(xIt->begin()); yIt != xIt->end(); yIt++)
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
			setTileSprite(SpriteManager::getInstance().getSprite("CursesA_ASCII "), sf::Vector2i(i,j));
		}
	}
}

void SFMLCursesWindow::setTileSprite(const sf::Sprite& lSprite, const sf::Vector2i& lTilePos)
{
	m_tiles[lTilePos.x][lTilePos.y] = lSprite;
	m_tiles[lTilePos.x][lTilePos.y].setPosition(static_cast<float>(lTilePos.y)*8.0f, static_cast<float>(lTilePos.x)*12.0f);
}
const sf::Sprite& SFMLCursesWindow::getTileSprite(const sf::Vector2i& lTilePos) const
{
	return m_tiles.at(lTilePos.x).at(lTilePos.y);
}

void SFMLCursesWindow::setCursesSize(const sf::Vector2i& lCursesSize)
{
	m_tiles.resize(lCursesSize.x);
	for(std::vector<std::vector<sf::Sprite>>::iterator yIt(m_tiles.begin()); yIt != m_tiles.end(); yIt++)
	{
		const int yIndex = yIt - m_tiles.begin();
		yIt->resize(lCursesSize.y, SpriteManager::getInstance().getSprite("CursesA_ASCII "));
		for(std::vector<sf::Sprite>::iterator xIt(yIt->begin()); xIt != yIt->end(); xIt++)
		{
			const int xIndex = xIt - yIt->begin();
			xIt->setPosition(static_cast<float>(xIndex)*8.0f, static_cast<float>(yIndex)*12.0f);
		}
	}
	m_cursesSize = lCursesSize;
}

sf::Vector2i SFMLCursesWindow::getCursesSize() const
{
	return m_cursesSize;
}