#include "StdAfx.h"
#include "GameState_InsurgencyGame.h"


GameState_InsurgencyGame::GameState_InsurgencyGame(void)
	: m_tileTypeDef(),
	m_creatureTypeDef(),
	m_itemTypeDef(),
	m_gameWorld(m_tileTypeDef, m_creatureTypeDef, m_itemTypeDef),
	m_turnTimer(m_gameWorld),
	m_playerCanAct(false)
{
}


GameState_InsurgencyGame::~GameState_InsurgencyGame(void)
{
}

void GameState_InsurgencyGame::OnAwake(void)
{
	m_gameWorld.test(std::pair<int,int>(-100,-100), std::pair<int,int>(100,100));
	WorldTile::ptr tile01(new WorldTile(m_gameWorld.m_tileTypeDef.getTileType(130)));
	WorldTile::ptr tile02(new WorldTile(m_gameWorld.m_tileTypeDef.getTileType(130)));
	WorldTile::ptr tile03(new WorldTile(m_gameWorld.m_tileTypeDef.getTileType(130)));

	m_gameWorld.setTile(std::pair<int,int>(0,0),std::move(tile01));
	m_gameWorld.setTile(std::pair<int,int>(6,-3),std::move(tile02));
	m_gameWorld.setTile(std::pair<int,int>(-2,-4),std::move(tile03));

	GameItem& item1(m_gameWorld.createItem(1));
	m_gameWorld.addItemToWorld(item1, std::pair<int,int>(1,0));
	GameItem& item2(m_gameWorld.createItem(2));
	m_gameWorld.addItemToWorld(item2, std::pair<int,int>(1,3));

	Creature& creature1(m_gameWorld.createCreature(1));
	m_gameWorld.addCreatureToWorld(creature1,std::pair<int,int>(2,0));
	m_gameWorld.setPlayerCreature(creature1);
	Creature& creature2(m_gameWorld.createCreature(1));
	m_gameWorld.addCreatureToWorld(creature2, std::pair<int,int>(-5,5));

	std::unique_ptr<SFMLGameWorldWindow> gameWorldWindow(new SFMLGameWorldWindow(m_gameWorld,std::pair<int,int>(0,0),std::pair<int,int>(20,20)));
	m_gameWorldWindow = gameWorldWindow.get();

	std::unique_ptr<sf::Text> turnCounter(new sf::Text());
	turnCounter->setPosition(300,300);
	m_turnCounter = turnCounter.get();
	std::unique_ptr<sf::Text> playerCoord(new sf::Text());
	playerCoord->setPosition(300,100);
	m_playerCoord = playerCoord.get();
	std::unique_ptr<sf::Text> playerInv(new sf::Text());
	playerInv->setPosition(300,200);
	m_playerInv = playerCoord.get();
	addDrawable(std::move(gameWorldWindow));
	addDrawable(std::move(turnCounter));
	addDrawable(std::move(playerCoord));
	addDrawable(std::move(playerInv));
}
void GameState_InsurgencyGame::OnUpdate(void)
{
	if(m_playerCanAct && m_gameWorld.getPlayerCreature()->getActTurnRem() != 0)
		m_playerCanAct = false;
	if(!m_playerCanAct)
	{
		Creature& creature = m_turnTimer.nextCreatureTurn();
		if(&creature == m_gameWorld.getPlayerCreature()) //it is now the player's turn
		{
			m_playerCanAct = true;
			m_gameWorldWindow->updateTiles(std::pair<int,int>(0,0));
		}
		else
		{
			//process NPC turns
			if(!m_turnTimer.moveCreatureRight(creature))
				m_turnTimer.waitCreature(creature);
		}
	}
}
void GameState_InsurgencyGame::OnRender(sf::RenderTarget& target)
{
	std::stringstream turnCount;
	turnCount<<m_turnTimer.getTurnCount();
	m_turnCounter->setString(turnCount.str());
	std::stringstream pCoord;
	pCoord <<'(';
	pCoord<<m_gameWorld.getPlayerCreature()->getLocation().first;
	pCoord<<',';
	pCoord<<m_gameWorld.getPlayerCreature()->getLocation().second;
	pCoord<<')';
	m_playerCoord->setString(pCoord.str());
	if(m_gameWorld.getPlayerCreature()->getInventoryComponent()->getNumEntities() == 0)
		m_playerInv->setString("No Items");
	else
	{
		std::string invItemsStr = "";
		std::vector<GameEntity*> invItems(m_gameWorld.getPlayerCreature()->getInventoryComponent()->getItemList());
		for(std::vector<GameEntity*>::const_iterator invIt(invItems.begin()); invIt != invItems.end(); invIt++)
		{
			invItemsStr += " ";
			invItemsStr += (*invIt)->getSName();
		}
		m_playerInv->setString(invItemsStr);
	}
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
	if(m_playerCanAct)
	{
	switch(key)
	{
	case sf::Keyboard::Right:
		m_turnTimer.moveCreatureRight(*m_gameWorld.getPlayerCreature());
		break;
	case sf::Keyboard::Up:
		m_turnTimer.moveCreatureUp(*m_gameWorld.getPlayerCreature());
		break;
	case sf::Keyboard::Left:
		m_turnTimer.moveCreatureLeft(*m_gameWorld.getPlayerCreature());
		break;
	case sf::Keyboard::Down:
		m_turnTimer.moveCreatureDown(*m_gameWorld.getPlayerCreature());
		break;
	case sf::Keyboard::Period:
		m_turnTimer.waitCreature(*m_gameWorld.getPlayerCreature());
		break;
	case sf::Keyboard::Comma:
		if(m_gameWorld.getItemPile(m_gameWorld.getPlayerCreature()->getLocation()))
		{
		m_turnTimer.creaturePickUpItem(*m_gameWorld.getPlayerCreature(),
			*m_gameWorld.getItemPile(m_gameWorld.getPlayerCreature()->getLocation())->front());
		}
		break;
	case sf::Keyboard::M:
		if(m_gameWorld.getPlayerCreature()->getInventoryComponent()->getNumEntities() != 0)
		{
			m_turnTimer.creatureDropItem(*m_gameWorld.getPlayerCreature(),
				dynamic_cast<GameItem&>(m_gameWorld.getPlayerCreature()->getInventoryComponent()->getEntityAtIndex(0)));
		}
		break;
	case sf::Keyboard::Escape:
		m_messages.push_back(new SFMLStateMessage_Close());
		break;
	}
	}
}