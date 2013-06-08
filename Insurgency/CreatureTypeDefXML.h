#pragma once
#include "ICreatureTypeDef.h"
#include "pugixml.hpp"
#include <vector>
#include <sstream>
class CreatureTypeDefXML : public ICreatureTypeDef
{
public:
	CreatureTypeDefXML(void);
	virtual ~CreatureTypeDefXML(void);

	virtual const CreatureType& getCreatureType(CreatureTypeID lTypeID) const;
private:
	std::vector<CreatureType> m_creatureTypes;
};

