#pragma once
#include "SFML-Template/SFMLStateInfo.h"
class Creature;
class GameTurnTimer;
class StateInfo_CreatureMenu :public SFMLStateInfo
{
public:
	StateInfo_CreatureMenu(Creature* creature, GameTurnTimer& gameTurnTimer)
		:m_creature(creature), m_gameTurnTimer(&gameTurnTimer) {}
	virtual ~StateInfo_CreatureMenu() {}
	Creature* m_creature;
	GameTurnTimer* m_gameTurnTimer;
};
