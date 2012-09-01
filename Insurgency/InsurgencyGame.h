#pragma once
#include "IWorldTileTypeDef.h"
#include "IGameItemTypeDef.h"
#include "ICreatureTypeDef.h"

#include "IGameWorld.h"
#include "IGameTurnTimer.h"

//input/output
#include "GameIOCurses.h"
#include "InputSourceListCurses.h"
class InsurgencyGame
{
public:
	InsurgencyGame(const IWorldTileTypeDef& lWorldTileTypeDef, const IGameItemTypeDef& lGameItemTypeDef,
				   const ICreatureTypeDef& lCreatureTypeDef, IGameWorld& lGameWorld, IGameTurnTimer& lGameTurnTimer);
	~InsurgencyGame(void);

	void update(void);

private:
	const IWorldTileTypeDef& m_WorldTileTypeDef;
	const IGameItemTypeDef& m_GameItemTypeDef;
	const ICreatureTypeDef& m_CreatureTypeDef;
	IGameWorld& m_GameWorld;
	IGameTurnTimer& m_GameTurnTimer;
};

