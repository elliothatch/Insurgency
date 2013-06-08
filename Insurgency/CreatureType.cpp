#include "stdafx.h"
#include "CreatureType.h"

CreatureType::CreatureType(void)
	:GameEntityType(),
	m_type(NULL),
	m_class(CreatureClassID::None)
{
	for(int i=0; i<CreatureStat::Count; i++)
	{
		m_baseStats[i] = 0;
	}
}

CreatureType::CreatureType(CreatureType&& other)
	:GameEntityType(std::move(other)),
	m_type(std::move(other.m_type)),
	m_class(std::move(other.m_class)),
	m_baseStats(std::move(other.m_baseStats))
{
}

CreatureType& CreatureType::operator=(CreatureType&& other)
{
	GameEntityType::operator=(static_cast<GameEntityType&&>(other));
	m_type = std::move(other.m_type);
	m_class = std::move(other.m_class);
	m_baseStats = std::move(other.m_baseStats);
	return *this;
}

CreatureType::~CreatureType()
{
}

//getters
CreatureTypeID CreatureType::getTypeID(void) const
{
	return m_type;
}
CreatureClassID::E CreatureType::getClassID(void) const 
{
	return m_class;
}
std::array<int,CreatureStat::Count> CreatureType::getBaseStats(void) const 
{
	return m_baseStats;
}
//setters
void CreatureType::setTypeID(CreatureTypeID lType) 
{
	m_type = lType;
}
void CreatureType::setClassID(CreatureClassID::E lClass) 
{
	m_class = lClass;
}
void CreatureType::setSpeed(int amount) 
{
	m_baseStats[CreatureStat::Speed] = amount;
}
void CreatureType::setStrength(int amount) 
{
	m_baseStats[CreatureStat::Strength] = amount;
}