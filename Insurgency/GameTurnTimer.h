#pragma once
//THIS IS VERY IMPORTANT!!!
//THIS IS TEMPORARILY THE CURSES TURN TIMER
//I NEED TO FIND A WAY TO DECOUPLE THE IO TYPE (CURSES/OPENGL) FROM THE TURN TIMER
#include "igameturntimer.h"
#include <algorithm>
//#include "IGameInput.h"
//HOPEFULLY I CAN REMOVE THIS INCLUDE
//#include "CharacterInputSourceCurses.h"
//#include "global.h"
//okay, rewriting the advance turn so it doesn't have anything to do with *taking* turns
//from now on it will only update the counters, etc.
class GameTurnTimer :
	public IGameTurnTimer
{
public:
	GameTurnTimer(IGameWorld& lGameWorld);
	virtual ~GameTurnTimer(void);

	virtual void advanceTurn(void);
	//virtual void processNPCTurns(void);
	virtual std::vector<Creature*> getCreaturesCanMove(void) const;

	//creature interactions
	virtual void moveCreature(Creature* lCreature, std::pair<int,int> loc);

private:
	//note: this should probably be replaced with an AI object or something
	//void processNPCTurn(void);

private:
	IGameWorld& gameWorld;
	unsigned long curTurn;
};

inline bool compareCreatureMoveOrder(Creature* a, Creature* b)
{
	//the one with a higher speed goes first
	return (a->getSpeed() > b->getSpeed());
}