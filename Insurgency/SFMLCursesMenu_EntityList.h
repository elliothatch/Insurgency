#pragma once
#include "SFMLCursesMenu.h"
#include "GameEntity.h"
#include <vector>
class SFMLCursesMenu_EntityList :
	public SFMLCursesMenu
{
public:
	SFMLCursesMenu_EntityList(const std::vector<GameEntity*>& lEntityList, const sf::Vector2i& lCharSize);
	virtual ~SFMLCursesMenu_EntityList(void);

	virtual void doActionAtIndex(unsigned int position);

private:
	std::vector<GameEntity*> m_entityList;
};

