#include "StdAfx.h"
#include "Creature.h"


Creature::Creature(const CreatureType& lType)
	:GameEntity(lType.getLName(), lType.getSName(), lType.getDName(), std::move(lType.cloneComponents())),
	m_type(lType.getTypeID()),
	m_class(lType.getClassID()),
	m_baseStats(lType.getBaseStats()),
	m_adjustedStats(lType.getBaseStats()),
	m_actTurnRem(0)
{
}


Creature::~Creature(void)
{
}

unsigned int Creature::getActTurnRem(void) 
{
	return m_actTurnRem;
}

void Creature::changeActTurnRem(unsigned int amount)
{
	m_actTurnRem += amount;
}
//get stats
int Creature::getSpeed(void) 
{
	return m_adjustedStats[CreatureStat::Speed];
}
int Creature::getStrength(void)
{
	return m_adjustedStats[CreatureStat::Strength];
}
int Creature::getBaseSpeed(void)
{
	return m_baseStats[CreatureStat::Speed];
}
int Creature::getBaseStrength(void)
{
	return m_baseStats[CreatureStat::Strength];
}
//change stats
void Creature::addTempStatEffect(CreatureStatEffect lStatEffect)
{
	//add stat
	m_statEffects.push_back(lStatEffect);
	//sort list
	std::sort(m_statEffects.begin(), m_statEffects.end(), compareStatEffectTimeRemaining);
	//change stat
	m_adjustedStats[lStatEffect.getAffectedStat()] += lStatEffect.getAmount();
}
void Creature::changeSpeedBase(int amount) 
{
	m_baseStats[CreatureStat::Speed] += amount;
}
void Creature::changeStrengthBase(int amount)
{
	m_baseStats[CreatureStat::Strength] += amount;
}
void Creature::turnUpdate(void)
{
	//
	//ActTurnRem Update
	//
	if(m_actTurnRem > 0)
		m_actTurnRem -= 1;
	//
	//StatEffect Update
	//
	//for each element in the list
	//decrease its remaining time by one and remove the effect if timeRemaining is at 0
	std::vector<CreatureStatEffect>::iterator statIt;
	for(statIt = m_statEffects.begin(); statIt != m_statEffects.end(); statIt++)
	{
		CreatureStatEffect statEf = (*statIt);
		statEf.changeTimeRemaining(-1);
		if(statEf.getTimeRemaining() == 0)
		{
			m_adjustedStats[statEf.getAffectedStat()] -= statEf.getAmount();
			m_statEffects.erase(statIt);
		}
	}
}

InventoryComponent* Creature::getInventoryComponent()
{
	return dynamic_cast<InventoryComponent*>(getComponent(EntityComponentID::Inventory));
}