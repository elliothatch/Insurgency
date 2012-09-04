#pragma once
//THIS IS VERY IMPORTANT!!!
//THIS IS TEMPORARILY THE CURSES TURN TIMER
//I NEED TO FIND A WAY TO DECOUPLE THE IO TYPE (CURSES/OPENGL) FROM THE TURN TIMER
#include "GameWorld.h"
#include <algorithm>
//#include "IGameInput.h"
//HOPEFULLY I CAN REMOVE THIS INCLUDE
//#include "CharacterInputSourceCurses.h"
//#include "global.h"
//okay, rewriting the advance turn so it doesn't have anything to do with *taking* turns
//from now on it will only update the counters, etc.
class GameTurnTimer
{
public:
	GameTurnTimer(GameWorld& lGameWorld);
	~GameTurnTimer(void);

	void advanceTurn(void);
	//void processNPCTurns(void);
	std::vector<Creature*> getCreaturesCanMove(void) const;

	//creature interactions
	void moveCreature(Creature& lCreature, std::pair<int,int> loc);

private:
	//note: this should probably be replaced with an AI object or something
	//void processNPCTurn(void);

private:
	GameWorld& m_gameWorld;
	unsigned long m_curTurn;
};

inline bool compareCreatureMoveOrder(Creature* a, Creature* b)
{
	//the one with a higher speed goes first
	return (a->getSpeed() > b->getSpeed());
}