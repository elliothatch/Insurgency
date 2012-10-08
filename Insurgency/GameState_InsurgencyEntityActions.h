#pragma once
#include "SFML-Template/GameStateBase.h"
class GameState_InsurgencyEntityActions
	:public GameStateBase
{
public:
	GameState_InsurgencyEntityActions(void);
	~GameState_InsurgencyEntityActions(void);

	virtual void OnAwake(const SFMLStateInfo* lStateInfo);
	virtual void OnUpdate(void);
	virtual void OnRender(sf::RenderTarget& target);
	virtual void OnCleanup(void);
	virtual void OnSuspend(void);
	virtual void OnResume(void);

	//SFMLEvent Overrides
	virtual void OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift);
};

