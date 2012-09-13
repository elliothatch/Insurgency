#include "StdAfx.h"
#include "GameState_InsurgencyGame.h"


GameState_InsurgencyGame::GameState_InsurgencyGame(void)
	: m_tileTypeDef(),
	m_creatureTypeDef(),
	m_itemTypeDef(),
	m_world(m_tileTypeDef, m_creatureTypeDef, m_itemTypeDef),
	m_turnTimer(m_world)
{
}


GameState_InsurgencyGame::~GameState_InsurgencyGame(void)
{
}

void GameState_InsurgencyGame::OnAwake(void)
{
	m_world.test(std::pair<int,int>(-100,-100), std::pair<int,int>(100,100));
	WorldTile::ptr tile01(new WorldTile(m_world.m_tileTypeDef.getTileType(128)));
	WorldTile::ptr tile02(new WorldTile(m_world.m_tileTypeDef.getTileType(128)));
	WorldTile::ptr tile03(new WorldTile(m_world.m_tileTypeDef.getTileType(128)));

	m_world.setTile(std::pair<int,int>(0,0),std::move(tile01));
	m_world.setTile(std::pair<int,int>(6,-3),std::move(tile02));
	m_world.setTile(std::pair<int,int>(-2,-4),std::move(tile03));

	std::unique_ptr<SFMLGameWorldWindow> gameWorldWindow(new SFMLGameWorldWindow(sf::Vector2f(160.0,240.0),m_world,sf::IntRect(-10,-10,20,20)));


	addDrawable(std::move(gameWorldWindow));
}
void GameState_InsurgencyGame::OnUpdate(void)
{
}
void GameState_InsurgencyGame::OnRender(sf::RenderTarget& target)
{
	GameStateBase::drawDisplayList(target);
}
void GameState_InsurgencyGame::OnCleanup(void)
{
	GameStateBase::Cleanup();
}
void GameState_InsurgencyGame::OnSuspend(void)
{
}
void GameState_InsurgencyGame::OnResume(void)
{
}

void GameState_InsurgencyGame::OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift)
{
	switch(key)
	{
	case sf::Keyboard::Escape:
		m_messages.push_back(new SFMLStateMessage_Close());
		break;
	}
}