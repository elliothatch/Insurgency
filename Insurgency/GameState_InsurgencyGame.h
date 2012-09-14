#pragma once
#include "SFML-Template/GameStateBase.h"
#include "SFMLGameWorldWindow.h"
#include "WorldTileTypeDef.h"
#include "CreatureTypeDef.h"
#include "GameItemTypeDef.h"
#include "GameWorld.h"
#include "GameTurnTimer.h"

#include <sstream>

class GameState_InsurgencyGame
	:public GameStateBase
{
public:
	GameState_InsurgencyGame(void);
	virtual ~GameState_InsurgencyGame(void);
	
	virtual void OnAwake(void);
	virtual void OnUpdate(void);
	virtual void OnRender(sf::RenderTarget& target);
	virtual void OnCleanup(void);
	virtual void OnSuspend(void);
	virtual void OnResume(void);

	//SFMLEvent Overrides
	virtual void OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift);

private:
	WorldTileTypeDef m_tileTypeDef;
	CreatureTypeDef m_creatureTypeDef;
	GameItemTypeDef m_itemTypeDef;
	GameWorld m_gameWorld;
	GameTurnTimer m_turnTimer;
	SFMLGameWorldWindow* m_gameWorldWindow;
	sf::Text* m_canMoveCounter;
	sf::Text* m_playerCoord;
	bool m_playerCanAct;
};

