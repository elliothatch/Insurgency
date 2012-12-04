#pragma once
#include "SFML-Template/SFMLStateInfo.h"
class Creature;
class StateInfo_Creature :public SFMLStateInfo
{
public:
	StateInfo_Creature(Creature* creature)
		:m_creature(creature) {}
	virtual ~StateInfo_Creature() {}
	Creature* m_creature;
};
