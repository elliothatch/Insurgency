#pragma once
#include <vector>
#include "IGameWorld.h"
class IGameOutput
{
public:

	IGameOutput(void)
	{
	}

	virtual ~IGameOutput(void)
	{
	}
	
	virtual void drawGameWorld(const IGameWorld& lWorld, std::pair<int,int> lCenterLoc) = 0;
};

