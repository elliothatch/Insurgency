#include "StdAfx.h"
#include "SFMLGameWorldWindow.h"


SFMLGameWorldWindow::SFMLGameWorldWindow(const sf::Vector2f& lPixelDimentions, const GameWorld& lGameWorld,
	const std::pair<int,int>& lWorldCenter, const std::pair<int,int>& lWorldSize)
	:SFMLGUIElement(),
	m_rectangle(lPixelDimentions),
	m_gameWorld(lGameWorld),
	m_worldRect(sf::Vector2i(lWorldCenter.first - lWorldSize.first/2, lWorldCenter.second - lWorldSize.second/2),
		sf::Vector2i(lWorldSize.first, lWorldSize.second))
{
	m_tiles.resize(m_worldRect.width);
	for(std::vector<std::vector<sf::Sprite>>::iterator xIt(m_tiles.begin()); xIt != m_tiles.end(); xIt++)
	{
		xIt->resize(m_worldRect.height);
	}
	updateTiles(lWorldCenter); 
}

SFMLGameWorldWindow::SFMLGameWorldWindow(const GameWorld& lGameWorld, const std::pair<int,int>& lWorldCenter, const std::pair<int,int>& lWorldSize)
	:SFMLGUIElement(),
	m_rectangle(sf::Vector2f(static_cast<float>(lWorldSize.first*8),static_cast<float>(lWorldSize.second*12))),
	m_gameWorld(lGameWorld),
	m_worldRect(sf::Vector2i(lWorldCenter.first - lWorldSize.first/2, lWorldCenter.second - lWorldSize.second/2),
		sf::Vector2i(lWorldSize.first, lWorldSize.second))
{
	m_tiles.resize(m_worldRect.width);
	for(std::vector<std::vector<sf::Sprite>>::iterator xIt(m_tiles.begin()); xIt != m_tiles.end(); xIt++)
	{
		xIt->resize(m_worldRect.height);
	}
	updateTiles(lWorldCenter); 
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

void SFMLGameWorldWindow::updateTiles(const std::pair<int,int>& lCenterPos)
{
	m_worldRect.left = lCenterPos.first - m_worldRect.width/2;
	m_worldRect.top = lCenterPos.second - m_worldRect.height/2;
	const float tileWidth = m_rectangle.getSize().x / m_worldRect.width;
	const float tileHeight = m_rectangle.getSize().y / m_worldRect.height;
	for(std::vector<std::vector<sf::Sprite>>::iterator xIt(m_tiles.begin()); xIt != m_tiles.end(); xIt++)
	{
		for(std::vector<sf::Sprite>::iterator yIt(xIt->begin()); yIt != xIt->end(); yIt++)
		{
			const int xIndex = xIt - m_tiles.begin();
			const int yIndex = yIt - xIt->begin();
			const std::pair<int,int> worldPos(m_worldRect.left + xIndex, m_worldRect.top + yIndex);
			//draw creatures first
			if(const Creature* creature = m_gameWorld.getCreature(worldPos))
			{
				*yIt = SpriteManager::getInstance().getSprite("CursesA_"+creature->getDName());
			}
			//draw items second
			else if(const std::vector<GameItem*>* itemPile = m_gameWorld.getItemPile(worldPos))
			{
				*yIt = SpriteManager::getInstance().getSprite("CursesA_"+itemPile->front()->getDName());
			}
			//draw tiles last
			else
			{
			const WorldTile& curTile(m_gameWorld.lookupTile(worldPos));
			*yIt = SpriteManager::getInstance().getSprite("CursesA_"+curTile.getTitle());
			}
			//position tile on screen
			const float xScale = tileWidth/(yIt->getLocalBounds().width);
			const float yScale = tileHeight/(yIt->getLocalBounds().height);
			yIt->setScale(xScale, yScale);
			yIt->setPosition(static_cast<float>(xIndex)*yIt->getLocalBounds().width*xScale,
				static_cast<float>(yIndex)*yIt->getLocalBounds().height*yScale);
		}
	}

}