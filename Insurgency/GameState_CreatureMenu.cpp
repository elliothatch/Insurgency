#include "StdAfx.h"
#include "GameState_CreatureMenu.h"


GameState_CreatureMenu::GameState_CreatureMenu(const sf::Window& window)
	:GameStateBase(window),
	m_creatureMenu(nullptr)
{
}


GameState_CreatureMenu::~GameState_CreatureMenu(void)
{
}

void GameState_CreatureMenu::OnAwake(const SFMLStateInfo* lStateInfo)
{
	//if the info is valid (inventory component)
	if(const StateInfo_CreatureMenu* creatureMenuInfo = dynamic_cast<const StateInfo_CreatureMenu*>(lStateInfo))
	{
		std::unique_ptr<SFMLUIMenu_Creature> creatureMenu(new SFMLUIMenu_Creature(*m_window,
			*creatureMenuInfo->m_gameTurnTimer,creatureMenuInfo->m_creature));
		m_creatureMenu = creatureMenu.get();
		addGUIElement(std::move(creatureMenu));
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
	GameStateBase::updateGUIElements();
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
	case sf::Keyboard::Up:
		m_creatureMenu->moveCursorUp();
		break;
	case sf::Keyboard::Down:
		m_creatureMenu->moveCursorDown();
		break;
	case sf::Keyboard::Return:
		m_creatureMenu->selectCursor();
		break;
	case sf::Keyboard::Escape:
		if(!m_creatureMenu->stepBack())
			m_messages.push_back(new SFMLStateMessage_PopState());
		break;
	}
}