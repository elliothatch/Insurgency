#pragma once
#include <array>
#include "ICreatureTypeDef.h"
class CreatureTypeDef : 
	public ICreatureTypeDef
{
	static const int kMaxCreatureTypes = 256;
public:
	CreatureTypeDef(void);
	virtual ~CreatureTypeDef(void);
	
	virtual const CreatureType& getCreatureType(CreatureTypeID lTypeID) const;
private:
	std::array<CreatureType, kMaxCreatureTypes> creatureTypes;
};

