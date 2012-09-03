#include "stdafx.h"
#include "CreatureType.h"

CreatureType::CreatureType(void)
	:GameEntityType(),
	m_type(NULL),
	m_class(CreatureClass_NoClass)
{
	for(int i=0; i<CreatureStatCount; i++)
	{
		m_baseStats[i] = 0;
	}
}

CreatureType::~CreatureType()
{
}

//getters
CreatureTypeID CreatureType::getTypeID(void) const
{
	return m_type;
}
CreatureClassID CreatureType::getClassID(void) const 
{
	return m_class;
}
std::array<int,CreatureStatCount> CreatureType::getBaseStats(void) const 
{
	return m_baseStats;
}
//setters
void CreatureType::setTypeID(CreatureTypeID lType) 
{
	m_type = lType;
}
void CreatureType::setClassID(CreatureClassID lClass) 
{
	m_class = lClass;
}
void CreatureType::setSpeed(int amount) 
{
	m_baseStats[CreatureStat_Speed] = amount;
}
void CreatureType::setStrength(int amount) 
{
	m_baseStats[CreatureStat_Strength] = amount;
}