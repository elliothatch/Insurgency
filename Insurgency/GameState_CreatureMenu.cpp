#include "StdAfx.h"
#include "GameState_CreatureMenu.h"


GameState_CreatureMenu::GameState_CreatureMenu(const sf::Window& window)
	:GameStateBase(window),
	m_creature(nullptr)
{
}


GameState_CreatureMenu::~GameState_CreatureMenu(void)
{
}

void GameState_CreatureMenu::OnAwake(const SFMLStateInfo* lStateInfo)
{
	//if the info is valid (inventory component)
	if(const StateInfo_Creature* creatureInfo = dynamic_cast<const StateInfo_Creature*>(lStateInfo))
	{
		m_creature = creatureInfo->m_creature;
		/*
		std::unique_ptr<UIMenu_EntityList> entityList(
			new UIMenu_EntityList(stateInfoInv->m_invComponent->getItemList(),
			sf::Vector2i(stateInfoInv->m_invComponent->getNumEntities(),15), *this));
		entityList->setIsActive(true);
		m_entityList = entityList.get();
		addGUIElement(std::move(entityList));
		*/
	}
}
void GameState_CreatureMenu::OnUpdate(void)
{
}
void GameState_CreatureMenu::OnRender(sf::RenderTarget& target)
{
	GameStateBase::drawDisplayList(target);
}
void GameState_CreatureMenu::OnCleanup(void)
{
	GameStateBase::Cleanup();
}
void GameState_CreatureMenu::OnSuspend(void)
{
}
void GameState_CreatureMenu::OnResume(void)
{
}

void GameState_CreatureMenu::OnKeyPressed(sf::Keyboard::Key key, bool alt, bool control, bool shift)
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