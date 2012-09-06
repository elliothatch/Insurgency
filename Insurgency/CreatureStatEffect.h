#pragma once
#include "CreatureStat.h"
class CreatureStatEffect
{
public:

	CreatureStatEffect(CreatureStat::E lStat, int lAmount, int lLength);
	~CreatureStatEffect(void);

	CreatureStat::E getAffectedStat(void) const;
	int getAmount(void) const;
	int getTimeRemaining(void) const;

	void setAffectedStat(CreatureStat::E lStat);
	void changeAmount(int amount);
	void changeTimeRemaining(int amount);

private:
	
	CreatureStat::E m_affectedStat;
	int m_amount;
	int m_timeRemaining;
};

