#pragma once
#include "IWorldTileTypeDef.h"
#include "IGameItemTypeDef.h"
#include "ICreatureTypeDef.h"
#include "GameWorld.h"
#include "GameTurnTimer.h"

//input/output
#include "GameIOCurses.h"
#include "InputSourceListCurses.h"
class InsurgencyGame
{
public:
	InsurgencyGame(const IWorldTileTypeDef& lWorldTileTypeDef, const IGameItemTypeDef& lGameItemTypeDef,
				   const ICreatureTypeDef& lCreatureTypeDef, GameWorld& lGameWorld, GameTurnTimer& lGameTurnTimer);
	~InsurgencyGame(void);

	void update(void);

private:
	const IWorldTileTypeDef& m_WorldTileTypeDef;
	const IGameItemTypeDef& m_GameItemTypeDef;
	const ICreatureTypeDef& m_CreatureTypeDef;
	GameWorld& m_GameWorld;
	GameTurnTimer& m_GameTurnTimer;
};

