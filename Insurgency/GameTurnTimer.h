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
	GameTurnTimer(GameWorld& gameWorld);
	~GameTurnTimer(void);

	void advanceTurn(void);
	Creature& nextCreatureTurn(void);
	//void processNPCTurns(void);
	std::vector<Creature*> getCreaturesCanMove(void) const;

	unsigned int getTurnCount() const;

	//creature interactions
	bool moveCreature(Creature& creature, std::pair<int,int> loc);
	bool moveCreatureRight(Creature& creature);
	bool moveCreatureUp(Creature& creature);
	bool moveCreatureLeft(Creature& creature);
	bool moveCreatureDown(Creature& creature);

	bool creaturePickUpItem(Creature& creature, GameItem& gameItem);
	bool creatureDropItem(Creature& creature, GameItem& gameItem);

	void waitCreature(Creature& creature);

	bool creatureEquipItem(Creature& creature, GameItem& gameItem, const GameEntityEquipGroups::EquipGroup& equipGroup);
	bool creatureUnequipItem(Creature& creature, GameItem& gameItem);

private:
	//note: this should probably be replaced with an AI object or something
	//void processNPCTurn(void);

private:
	GameWorld* m_gameWorld;
	unsigned long m_curTurn;
	std::vector<Creature*> m_actingCreatures;
};