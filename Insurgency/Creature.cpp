#include "StdAfx.h"
#include "Creature.h"


Creature::Creature(const CreatureType& lType, std::pair<int,int> loc)
	:GameEntity(loc),
	m_type(lType.getTypeID()),
	m_class(lType.getClassID()),
	baseStats(lType.getBaseStats()),
	adjustedStats(lType.getBaseStats())
{
	setLName(lType.getLName());
	setSName(lType.getSName());
	m_components = lType.getComponents();
}


Creature::~Creature(void)
{	
	//delete any effects remaining
	std::vector<CreatureStatEffect*>::iterator statIt;
	for(statIt = statEffects.begin(); statIt != statEffects.end(); statIt++)
	{
		delete (*statIt);
	}
}

void Creature::addTempStatEffect(CreatureStatEffect* lStatEffect)
{
	//add stat
	statEffects.push_back(lStatEffect);
	//sort list
	std::sort(statEffects.begin(), statEffects.end(), compareStatEffectTimeRemaining);
	//change stat
	adjustedStats[lStatEffect->getAffectedStat()] += lStatEffect->getAmount();
}

void Creature::turnUpdate(void)
{
	//
	//ActTurnRem Update
	//
	if(actTurnRem > 0)
		actTurnRem -= 1;
	//
	//StatEffect Update
	//
	//for each element in the list
	//decrease its remaining time by one and remove the effect if timeRemaining is at 0
	std::vector<CreatureStatEffect*>::iterator statIt;
	for(statIt = statEffects.begin(); statIt != statEffects.end(); statIt++)
	{
		CreatureStatEffect* statEf = (*statIt);
		statEf->changeTimeRemaining(-1);
		if(statEf->getTimeRemaining() == 0)
		{
			adjustedStats[statEf->getAffectedStat()] -= statEf->getAmount();
			delete statEf;
			statEffects.erase(statIt);
		}
	}
}