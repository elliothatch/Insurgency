#pragma once
class CreatureStatEffect
{
public:

	CreatureStatEffect(void)
	{
	}

	~CreatureStatEffect(void)
	{
	}

	int getAffectedStat(void) const {return affectedStat;}
	int getAmount(void) const {return amount;}
	int getTimeRemaining(void) const {return timeRemaining;}

	void changeTimeRemaining(int amount) {timeRemaining += amount;}

private:
	
	int affectedStat;
	int amount;
	int timeRemaining;
};

