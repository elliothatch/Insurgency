#include "stdafx.h"
#include "CreatureStatEffect.h"

CreatureStatEffect::CreatureStatEffect(CreatureStat::E lStat, int lAmount, int lLength)
	:m_affectedStat(lStat), m_amount(lAmount), m_timeRemaining(lLength)
{
}

CreatureStatEffect::~CreatureStatEffect()
{
}

CreatureStat::E CreatureStatEffect::getAffectedStat(void) const
{
	return m_affectedStat;
}
int CreatureStatEffect::getAmount(void) const 
{
	return m_amount;
}
int CreatureStatEffect::getTimeRemaining(void) const
{
	return m_timeRemaining;
}

void CreatureStatEffect::setAffectedStat(CreatureStat::E lStat)
{
	m_affectedStat = lStat;
}

void CreatureStatEffect::changeAmount(int amount)
{
	m_amount += amount;
}

void CreatureStatEffect::changeTimeRemaining(int amount)
{
	m_timeRemaining += amount;
}
