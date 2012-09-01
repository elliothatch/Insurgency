#pragma once
#include "ICreatureTypeDef.h"
class CreatureTypeDef : 
	public ICreatureTypeDef
{
public:
	CreatureTypeDef(void);
	virtual ~CreatureTypeDef(void);
	
	virtual const CreatureType& getCreatureType(CreatureTypeID lTypeID) const;
private:
#define MAXCREATURETYPES 256
	CreatureType creatureTypes[MAXCREATURETYPES];
};

