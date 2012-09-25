#include "StdAfx.h"
#include "SFMLWorldItemsWindow.h"


SFMLWorldItemsWindow::SFMLWorldItemsWindow(const sf::Vector2i& lCharSize, const GameWorld& lGameWorld, std::pair<int,int> lWorldPoint)
	:m_cursesWindow(lCharSize),
	 m_gameWorld(lGameWorld),
	 m_worldPoint(lWorldPoint)
{
	update(lWorldPoint); 
}


SFMLWorldItemsWindow::~SFMLWorldItemsWindow(void)
{
}

void SFMLWorldItemsWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_cursesWindow, states);
}

sf::FloatRect SFMLWorldItemsWindow::getLocalBounds(void) const
{
	return m_cursesWindow.getLocalBounds();
}
sf::FloatRect SFMLWorldItemsWindow::getGlobalBounds(void) const
{
	return getTransform().transformRect(m_cursesWindow.getGlobalBounds());
}

void SFMLWorldItemsWindow::update(std::pair<int,int> lWorldPoint)
{
	m_worldPoint = lWorldPoint;
	std::vector<GameItem*>* gameItemPile(m_gameWorld.getItemPile(m_worldPoint));
	m_cursesWindow.clearTiles();
	if(gameItemPile)
	{
		for(std::vector<GameItem*>::const_iterator pileIt(gameItemPile->begin()); pileIt != gameItemPile->end(); pileIt++)
		{
			const int yIndex = pileIt - gameItemPile->begin();
			const std::string& itemSName((*pileIt)->getSName());
			for(unsigned int i = 0; i<itemSName.length(); i++)
			{
				m_cursesWindow.setTileSprite(SpriteManager::getInstance().getSprite(std::string("CursesA_ASCII") + itemSName.at(i)),
					sf::Vector2i(yIndex, i));
			}
		}
	}
}