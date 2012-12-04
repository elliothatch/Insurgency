#include "StdAfx.h"
#include "GameState_InsurgencyEntityActions.h"


GameState_InsurgencyEntityActions::GameState_InsurgencyEntityActions(const sf::Window& window)
	:GameStateBase(window)
{
}


GameState_InsurgencyEntityActions::~GameState_InsurgencyEntityActions(void)
{
}
void GameState_InsurgencyEntityActions::OnAwake(const SFMLStateInfo* lStateInfo)
{
	//if the info is valid (inventory component)
	if(const SFMLStateInfo_EntityActions* stateInfo = dynamic_cast<const SFMLStateInfo_EntityActions*>(lStateInfo))
	{
		addDrawable(std::move(std::unique_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(10.0f,10.0f)))));
		/*
		std::unique_ptr<UIMenu_EntityList> entityList(
			new UIMenu_EntityList(stateInfoInv->m_invComponent->getItemList(),
			sf::Vector2i(stateInfoInv->m_invComponent->getNumEntities(),15)));
		entityList->setIsActive(true);
		m_entityList = entityList.get();
		addGUIElement(std::move(entityList));
		*/
	
	}
}
void GameState_InsurgencyEntityActions::OnUpdate(void)
{
}
void GameState_InsurgencyEntityActions::OnRender(sf::RenderTarget& target)
{
	GameStateBase::drawDisplayList(target);
}
void GameState_InsurgencyEntityActions::OnCleanup(void)
{
	GameStateBase::Cleanup();
}
void GameState_InsurgencyEntityActions::OnSuspend(void)
{
}
void GameState_InsurgencyEntityActions::OnResume(void)
{
}

void GameState_InsurgencyEntityActions::OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift)
{
	switch(key)
	{
		/*
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
		*/
	case sf::Keyboard::Escape:
		m_messages.push_back(new SFMLStateMessage_PopState());
		break;
	}
}