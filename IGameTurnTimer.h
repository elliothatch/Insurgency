#pragma once
#include "IGameWorld.h"
#include <vector>
class IGameTurnTimer
{
public:

	IGameTurnTimer(IGameWorld& lGameWorld)
	{
	}

	virtual ~IGameTurnTimer(void)
	{
	}

	virtual void advanceTurn(void) = 0;
	virtual std::vector<Creature*> getCreaturesCanMove(void) const = 0;
	//is this the best way to implement this?
	//virtual void processNPCTurns(void) = 0;

	virtual void moveCreature(Creature* lCreature, std::pair<int,int> loc) = 0;
};

