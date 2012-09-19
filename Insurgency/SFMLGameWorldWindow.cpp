#include "StdAfx.h"
#include "SFMLGameWorldWindow.h"

SFMLGameWorldWindow::SFMLGameWorldWindow(const GameWorld& lGameWorld, const std::pair<int,int>& lWorldCenter, const std::pair<int,int>& lWorldSize)
	:SFMLGUIElement(),
	m_cursesWindow(sf::Vector2i(lWorldSize.second, lWorldSize.first)),
	m_gameWorld(lGameWorld),
	m_worldRect(sf::Vector2i(lWorldCenter.first - lWorldSize.first/2, lWorldCenter.second - lWorldSize.second/2),
		sf::Vector2i(lWorldSize.first, lWorldSize.second))
{
	updateTiles(lWorldCenter);
}

SFMLGameWorldWindow::~SFMLGameWorldWindow(void)
{
}

void SFMLGameWorldWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_cursesWindow, states);
}
sf::FloatRect SFMLGameWorldWindow::getLocalBounds(void) const
{
	return m_cursesWindow.getLocalBounds();
}
sf::FloatRect SFMLGameWorldWindow::getGlobalBounds(void) const
{
	return getTransform().transformRect(m_cursesWindow.getGlobalBounds());
}

void SFMLGameWorldWindow::updateTiles(const std::pair<int,int>& lCenterPos)
{
	m_worldRect.left = lCenterPos.first - m_worldRect.width/2;
	m_worldRect.top = lCenterPos.second - m_worldRect.height/2;
	for(int i = 0; i< m_cursesWindow.getCursesSize().y; i++)
	{
		for(int j = 0; j < m_cursesWindow.getCursesSize().x; j++)
		{
			const std::pair<int,int> worldPos(m_worldRect.left + i, m_worldRect.top + j);
			//draw creatures first
			if(const Creature* creature = m_gameWorld.getCreature(worldPos))
			{
				m_cursesWindow.setTileSprite(SpriteManager::getInstance().getSprite("CursesA_"+creature->getDName()), sf::Vector2i(j,i));
			}
			//draw items second
			else if(const std::vector<GameItem*>* itemPile = m_gameWorld.getItemPile(worldPos))
			{
				m_cursesWindow.setTileSprite(SpriteManager::getInstance().getSprite("CursesA_"+itemPile->front()->getDName()),sf::Vector2i(j,i));
			}
			//draw tiles last
			else
			{
			const WorldTile& curTile(m_gameWorld.lookupTile(worldPos));
			m_cursesWindow.setTileSprite(SpriteManager::getInstance().getSprite("CursesA_"+curTile.getTitle()),sf::Vector2i(j,i));
			}
		}
	}
}