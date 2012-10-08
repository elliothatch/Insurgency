#pragma once
#include "SFML-Template/GameStateBase.h"
#include "InventoryComponent.h"
//#include "SFMLCursesMenu_EntityList.h"
class GameState_InsurgencyInventory
	:public GameStateBase
{
public:
	GameState_InsurgencyInventory(void);
	virtual ~GameState_InsurgencyInventory(void);

	virtual void OnAwake(const SFMLStateInfo* lStateInfo);
	virtual void OnUpdate(void);
	virtual void OnRender(sf::RenderTarget& target);
	virtual void OnCleanup(void);
	virtual void OnSuspend(void);
	virtual void OnResume(void);

	//SFMLEvent Overrides
	virtual void OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift);
private:
	InventoryComponent* m_inventory;
	//SFMLCursesMenu_EntityList* m_entityList;
};

