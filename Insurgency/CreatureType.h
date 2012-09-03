#pragma once
#include "GameEntityType.h"
#include <array>
typedef unsigned int CreatureTypeID; //unique type identifier for this creature type
//non-unique type for catagorizing creatures (i.e. policePatrol01 [weak police patrolman]) (note, only for where they spawn)
enum CreatureClassID
{
	CreatureClass_NoClass = 0,
	CreatureClass_Insurgent01,
	CreatureClassCount
	
};
enum CreatureStat
	{
		CreatureStat_Speed = 0,
		CreatureStat_Strength,
		CreatureStatCount,
	};

class CreatureType : public GameEntityType
{
public:

	CreatureType(void);
	~CreatureType(void);

	//getters
	CreatureTypeID getTypeID(void) const;
	CreatureClassID getClassID(void) const;
	std::array<int,CreatureStatCount> getBaseStats(void) const;
	//setters
	void setTypeID(CreatureTypeID lType);
	void setClassID(CreatureClassID lClass);
	void setSpeed(int amount);
	void setStrength(int amount);

private:
	CreatureTypeID m_type;
	CreatureClassID m_class;
	std::array<int, CreatureStatCount> m_baseStats;
};

