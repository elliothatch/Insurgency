#include "StdAfx.h"
#include "SFMLCursesMenu_EntityList.h"


SFMLCursesMenu_EntityList::SFMLCursesMenu_EntityList(const std::vector<GameEntity*>& lEntityList, const sf::Vector2i& lCharSize,
	GameStateBase& gameState)
	:SFMLCursesMenu(lCharSize, "Inventory Empty"),
	 m_entityList(lEntityList),
	 m_gameState(gameState)
{
	unsigned int index = 0;
	for(std::vector<GameEntity*>::const_iterator entityIt(m_entityList.begin()); entityIt != m_entityList.end(); entityIt++)
	{
		setLineText((*entityIt)->getSName(), index);
		index++;
	}
	moveKeyboardCursorToPosition(0);
}


SFMLCursesMenu_EntityList::~SFMLCursesMenu_EntityList(void)
{
}

void SFMLCursesMenu_EntityList::doActionAtIndex(unsigned int position)
{
	printf("Do Action at %d\n", position);
	m_gameState.addStateMessage(new SFMLStateMessage_PushState("InsurgencyEntityActions",
			std::unique_ptr<SFMLStateInfo_EntityActionsState>(new SFMLStateInfo_EntityActionsState
			(200,200,m_entityList.at(m_keyboardCursorPos)))));
	
}