#pragma once
class CreatureStatEffect
{
public:

	CreatureStatEffect(void);
	~CreatureStatEffect(void);

	int getAffectedStat(void) const;
	int getAmount(void) const;
	int getTimeRemaining(void) const;

	void changeTimeRemaining(int amount);

private:
	
	int m_affectedStat;
	int m_amount;
	int m_timeRemaining;
};

