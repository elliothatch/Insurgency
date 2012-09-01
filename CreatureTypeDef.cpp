#include "StdAfx.h"
#include "CreatureTypeDef.h"


CreatureTypeDef::CreatureTypeDef(void)
{
	for(int i = 0; i<MAXCREATURETYPES; i++)
	{
		creatureTypes[i].setTypeID(i);
	}
	creatureTypes[1].setLName("Insurgent");
	creatureTypes[1].setSName("Elliot Hatch");
	creatureTypes[1].setClassID(insurgent01);
	creatureTypes[1].setSpeed(5);
	creatureTypes[1].setStrength(6);
}


CreatureTypeDef::~CreatureTypeDef(void)
{
}

const CreatureType& CreatureTypeDef::getCreatureType(CreatureTypeID lTypeID) const
{
	return creatureTypes[lTypeID];
}