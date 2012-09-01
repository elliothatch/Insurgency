#include "StdAfx.h"
#include "CreatureInputSourceCurses.h"


CreatureInputSourceCurses::CreatureInputSourceCurses(void)
{
}


CreatureInputSourceCurses::~CreatureInputSourceCurses(void)
{
}

InputMessage* CreatureInputSourceCurses::processInput(chtype chIn)
{
	switch(chIn)
	{
	case 27: //escape
		return new Msg_OpenPauseMenu();
		break;
	default:
		return new Msg_None();
	}
}