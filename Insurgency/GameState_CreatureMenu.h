#pragma once
#include "SFML-Template/GameStateBase.h"
#include "InventoryComponent.h"
#include "StateInfo_Creature.h"
//#include "UIMenu_EntityList.h"
class GameState_CreatureMenu
	:public GameStateBase
{
public:
	GameState_CreatureMenu(const sf::Window& window);
	virtual ~GameState_CreatureMenu(void);

	virtual void OnAwake(const SFMLStateInfo* lStateInfo);
	virtual void OnUpdate(void);
	virtual void OnRender(sf::RenderTarget& target);
	virtual void OnCleanup(void);
	virtual void OnSuspend(void);
	virtual void OnResume(void);

	//SFMLEvent Overrides
	virtual void OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift);
private:
	Creature* m_creature;
	//UIMenu_EntityList* m_entityList;
};

