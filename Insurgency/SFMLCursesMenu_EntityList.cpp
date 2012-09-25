#include "StdAfx.h"
#include "SFMLCursesMenu_EntityList.h"


SFMLCursesMenu_EntityList::SFMLCursesMenu_EntityList(const std::vector<GameEntity*>& lEntityList, const sf::Vector2i& lCharSize)
	:SFMLCursesMenu(lCharSize, "Inventory Empty"),
	 m_entityList(lEntityList)
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
}