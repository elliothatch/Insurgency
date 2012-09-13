#include "StdAfx.h"
#include "SFMLGameWorldWindow.h"


SFMLGameWorldWindow::SFMLGameWorldWindow(const sf::Vector2f& lPixelDimentions, const GameWorld& lGameWorld, const sf::IntRect& lWorldRect)
	:SFMLGUIElement(),
	m_rectangle(lPixelDimentions),
	m_gameWorld(lGameWorld),
	m_worldRect(lWorldRect)
{
	const float tileWidth = lPixelDimentions.x / lWorldRect.width;
	const float tileHeight = lPixelDimentions.y / lWorldRect.height;
	m_tiles.resize(m_worldRect.width);
	for(std::vector<std::vector<sf::Sprite>>::iterator xIt(m_tiles.begin()); xIt != m_tiles.end(); xIt++)
	{
		xIt->resize(m_worldRect.height);
		for(std::vector<sf::Sprite>::iterator yIt(xIt->begin()); yIt != xIt->end(); yIt++)
		{
			const int xIndex = xIt - m_tiles.begin();
			const int yIndex = yIt - xIt->begin();
			const WorldTile& curTile(m_gameWorld.lookupTile(std::pair<int,int>(lWorldRect.left+xIndex,lWorldRect.top+yIndex)));
			std::stringstream tileID;
			tileID << curTile.getDisplayID();
			*yIt = SpriteManager::getInstance().getSprite("CursesA_"+tileID.str());
			const float xScale = tileWidth/(yIt->getLocalBounds().width);
			const float yScale = tileHeight/(yIt->getLocalBounds().height);
			yIt->setScale(xScale, yScale);
			yIt->setPosition(static_cast<float>(xIndex)*yIt->getLocalBounds().width*xScale,
				static_cast<float>(yIndex)*yIt->getLocalBounds().height*yScale);
		}
	}

}

SFMLGameWorldWindow::~SFMLGameWorldWindow(void)
{
}

void SFMLGameWorldWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const
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
sf::FloatRect SFMLGameWorldWindow::getLocalBounds(void) const
{
	return m_rectangle.getLocalBounds();
}
sf::FloatRect SFMLGameWorldWindow::getGlobalBounds(void) const
{
	return getTransform().transformRect(m_rectangle.getGlobalBounds());
}

void SFMLGameWorldWindow::updateTiles()
{
	
	for(std::vector<std::vector<sf::Sprite>>::iterator xIt(m_tiles.begin()); xIt != m_tiles.end(); xIt++)
	{
		for(std::vector<sf::Sprite>::iterator yIt(xIt->begin()); yIt != xIt->end(); yIt++)
		{
			
		}
	}
}