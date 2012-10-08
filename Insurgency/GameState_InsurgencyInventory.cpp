#include "StdAfx.h"
#include "GameState_InsurgencyInventory.h"


GameState_InsurgencyInventory::GameState_InsurgencyInventory(void)
{
}


GameState_InsurgencyInventory::~GameState_InsurgencyInventory(void)
{
}

void GameState_InsurgencyInventory::OnAwake(const SFMLStateInfo* lStateInfo)
{
	//if the info is valid (inventory component)
	if(const SFMLStateInfo_InventoryComponent* stateInfoInv = dynamic_cast<const SFMLStateInfo_InventoryComponent*>(lStateInfo))
	{
		m_inventory = stateInfoInv->m_invComponent;
		std::unique_ptr<SFMLCursesMenu_EntityList> entityList(
			new SFMLCursesMenu_EntityList(stateInfoInv->m_invComponent->getItemList(),
			sf::Vector2i(stateInfoInv->m_invComponent->getNumEntities(),15), *this));
		entityList->setIsActive(true);
		m_entityList = entityList.get();
		addGUIElement(std::move(entityList));
	}
}
void GameState_InsurgencyInventory::OnUpdate(void)
{
}
void GameState_InsurgencyInventory::OnRender(sf::RenderTarget& target)
{
	GameStateBase::drawDisplayList(target);
}
void GameState_InsurgencyInventory::OnCleanup(void)
{
	GameStateBase::Cleanup();
}
void GameState_InsurgencyInventory::OnSuspend(void)
{
}
void GameState_InsurgencyInventory::OnResume(void)
{
}

void GameState_InsurgencyInventory::OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift)
{
	switch(key)
	{
	case sf::Keyboard::Up:
		m_entityList->moveKeyboardCursorUp();
		break;
	case sf::Keyboard::Down:
		m_entityList->moveKeyboardCursorDown();
		break;
	case sf::Keyboard::Return:
		m_entityList->selectKeyboardCursor();
		break;
	case sf::Keyboard::A:
		m_entityList->setIsActive(!m_entityList->getIsActive());
		break;
	case sf::Keyboard::Escape:
		m_messages.push_back(new SFMLStateMessage_PopState());
		break;
	}
}