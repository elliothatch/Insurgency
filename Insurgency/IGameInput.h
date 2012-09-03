#pragma once
#include "GameTurnTimer.h"
#include "IInputSource.h"
class IGameInput
{
public:

	IGameInput(void)
	{
	}

	virtual ~IGameInput(void)
	{
	}

	virtual void addInputSource(IInputSource* lInputSource) = 0;

	virtual void getInput(void) = 0;

protected:
	virtual void decipherMessage(InputMessage* lMsg) = 0; //should delete message when done
};