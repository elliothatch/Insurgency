#pragma once
#include "GameEntityType.h"
#include <array>
typedef unsigned int CreatureTypeID; //unique type identifier for this creature type
//non-unique type for catagorizing creatures (i.e. policePatrol01 [weak police patrolman]) (note, only for where they spawn)
enum CreatureClassID
{
	NOCREATURECLASS = 0,
	insurgent01,
	
};
enum CreatureStat
	{
		SPEED = 0,
		STRENGTH,
		STATNUM,
	};

class CreatureType : public GameEntityType
{
public:

	CreatureType(void)
		:GameEntityType(),
		m_type(NULL),
		m_class(NOCREATURECLASS)
	{
		for(int i=0; i<STATNUM; i++)
		{
			baseStats[i] = 0;
		}
	}

	~CreatureType(void)
	{
	}

	//getters
	CreatureTypeID getTypeID(void) const {return m_type;}
	CreatureClassID getClassID(void) const {return m_class;}
	std::array<int,STATNUM> getBaseStats(void) const {return baseStats;}
	//setters
	void setTypeID(CreatureTypeID lType) {m_type = lType;}
	void setClassID(CreatureClassID lClass) {m_class = lClass;}
	void setSpeed(int amount) {baseStats[SPEED] = amount;}
	void setStrength(int amount) {baseStats[STRENGTH] = amount;}

private:
	CreatureTypeID m_type;
	CreatureClassID m_class;
	std::array<int, STATNUM> baseStats;
};

