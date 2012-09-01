#include "StdAfx.h"
#include "InsurgencyGame.h"


InsurgencyGame::InsurgencyGame(const IWorldTileTypeDef& lWorldTileTypeDef, const IGameItemTypeDef& lGameItemTypeDef,
				   const ICreatureTypeDef& lCreatureTypeDef, IGameWorld& lGameWorld, IGameTurnTimer& lGameTurnTimer)
				   :m_WorldTileTypeDef(lWorldTileTypeDef),
				    m_GameItemTypeDef(lGameItemTypeDef),
					m_CreatureTypeDef(lCreatureTypeDef),
					m_GameWorld(lGameWorld),
					m_GameTurnTimer(lGameTurnTimer)
{
}


InsurgencyGame::~InsurgencyGame(void)
{
}

void InsurgencyGame::update(void)
{
}