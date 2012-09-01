#pragma once
#include "gameentity.h"
#include "CreatureType.h"
#include "CreatureStatEffect.h"
#include <vector>
#include <algorithm>
#include <array>

class Creature :
	public GameEntity
{

public:
	Creature(const CreatureType& lType, std::pair<int,int> loc);
	virtual ~Creature(void);

	unsigned int getActTurnRem(void) {return actTurnRem;}

	void changeActTurnRem(unsigned int amount) {actTurnRem += amount;}
	
	//get stats
	int getSpeed(void) {return adjustedStats[SPEED];}
	int getStrength(void) {return adjustedStats[STRENGTH];}

	int getBaseSpeed(void) {return baseStats[SPEED];}
	int getBaseStrength(void) {return baseStats[STRENGTH];}

	//change stats
	void addTempStatEffect(CreatureStatEffect* lStatEffect);
	void changeSpeedBase(int amount) {baseStats[SPEED] += amount;}
	void changeStrengthBase(int amount) {baseStats[STRENGTH] += amount;}

	//update the creature's turn
	void turnUpdate(void);
private:
	std::array<int, STATNUM> baseStats;
	std::array<int, STATNUM> adjustedStats;

	std::vector<CreatureStatEffect*> statEffects;

	//how many turns until the action is finished.
	//interruptable actions need a little more framework
	unsigned int actTurnRem;

	//don't think I need these
	CreatureTypeID m_type;
	CreatureClassID m_class;
};


inline bool compareStatEffectTimeRemaining(CreatureStatEffect* a, CreatureStatEffect* b)
	{
		return (a->getTimeRemaining() < b->getTimeRemaining());
	}