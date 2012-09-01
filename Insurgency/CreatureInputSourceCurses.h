#pragma once
#include "IInputSourceCurses.h"
class CreatureInputSourceCurses :
	public IInputSourceCurses
{
public:
	CreatureInputSourceCurses(void);
	virtual ~CreatureInputSourceCurses(void);

	virtual InputMessage* processInput(chtype chIn);
};

