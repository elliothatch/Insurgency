#pragma once
#include <vector>
#include "GameWorld.h"
class IGameOutput
{
public:

	IGameOutput(void)
	{
	}

	virtual ~IGameOutput(void)
	{
	}
	
	virtual void drawGameWorld(const GameWorld& lWorld, std::pair<int,int> lCenterLoc) = 0;
};

