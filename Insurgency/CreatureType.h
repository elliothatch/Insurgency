#pragma once
#include "GameEntityType.h"
#include "CreatureStat.h"
#include <array>
typedef unsigned int CreatureTypeID; //unique type identifier for this creature type
//non-unique type for catagorizing creatures (i.e. policePatrol01 [weak police patrolman]) (note, only for where they spawn)
struct CreatureClassID
{
	enum E
	{
		None = 0,
		Insurgent01,
		Count
	
	};
};

class CreatureType : public GameEntityType
{
public:

	CreatureType(void);
	~CreatureType(void);

	//getters
	CreatureTypeID getTypeID(void) const;
	CreatureClassID::E getClassID(void) const;
	std::array<int,CreatureStat::Count> getBaseStats(void) const;
	//setters
	void setTypeID(CreatureTypeID lType);
	void setClassID(CreatureClassID::E lClass);
	void setSpeed(int amount);
	void setStrength(int amount);

private:
	CreatureTypeID m_type;
	CreatureClassID::E m_class;
	std::array<int, CreatureStat::Count> m_baseStats;
};

