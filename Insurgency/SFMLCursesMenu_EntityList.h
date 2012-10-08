#pragma once
#include "SFMLCursesMenu.h"
#include "GameEntity.h"
#include <vector>
#include "SFML-Template/GameStateBase.h"
class SFMLCursesMenu_EntityList :
	public SFMLCursesMenu
{
public:
	SFMLCursesMenu_EntityList(const std::vector<GameEntity*>& lEntityList, const sf::Vector2i& lCharSize, GameStateBase& gameState);
	virtual ~SFMLCursesMenu_EntityList(void);

	virtual void doActionAtIndex(unsigned int position);

private:
	GameStateBase& m_gameState;
	std::vector<GameEntity*> m_entityList;
};

