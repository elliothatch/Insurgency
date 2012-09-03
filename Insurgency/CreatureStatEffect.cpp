#include "stdafx.h"
#include "CreatureStatEffect.h"

CreatureStatEffect::CreatureStatEffect()
	:m_affectedStat(0), m_amount(0), m_timeRemaining(0)
{
}

CreatureStatEffect::~CreatureStatEffect()
{
}

int CreatureStatEffect::getAffectedStat(void) const
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
void CreatureStatEffect::changeTimeRemaining(int amount)
{
	m_timeRemaining += amount;
}
