#pragma once
#include "iinputsource.h"
#include <curses.h>
class IInputSourceCurses :
	public IInputSource
{
public:

	IInputSourceCurses(void)
	{
	}

	virtual ~IInputSourceCurses(void)
	{
	}

	virtual InputMessage* processInput(chtype chIn) = 0;
};

