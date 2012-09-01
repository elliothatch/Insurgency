#pragma once
#include <vector>
#include "IWorldTile.h"
class IWorldRegion
{
public:

	IWorldRegion(void)
	{
	}

	virtual ~IWorldRegion(void)
	{
	}
	virtual int getSize(void) const = 0;
	virtual IWorldTile* getTile(std::pair<int,int> loc) = 0;
	virtual void setTile(std::pair<int,int> loc, IWorldTile* ltile) = 0;
	virtual void save(void) = 0;
	virtual void load(void) = 0;
};

