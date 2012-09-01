#include "StdAfx.h"
#include "GameIOCurses.h"


GameIOCurses::GameIOCurses(void)
{
	//initialize curses
	initscr();
	raw();
	noecho();
	curs_set(0);

	//initialize color
	start_color();
	int a = 0;
	for(int b=0; b<16; b++)
	{
		for(int c=0; c<16; c++)
		{
			init_pair(a++,c,b);
		}
	}
	//input window
	inputWindow = new CursesWindow(0,0,1,1);
	inputWindow->setKeypad(true);
	inputWindow->setInputTimeout(0);
}


GameIOCurses::~GameIOCurses(void)
{
	std::vector<CursesWindow*>::iterator winIt(windowList.begin());
	for(winIt; winIt != windowList.end(); winIt++)
	{
		delete (*winIt);
	}
	delete inputWindow;
}

//output

void GameIOCurses::drawGameWorld(const IGameWorld& lWorld, std::pair<int,int> lCenterLoc)
{
	//temp check, only window is the gameworld window
	std::vector<CursesWindow*>::iterator winIt(windowList.begin());
	if(winIt != windowList.end())
	{
		CursesGameWorldWindow* lGameWorldWindow = static_cast<CursesGameWorldWindow*>(*winIt);
		lGameWorldWindow->refWin(lWorld, lCenterLoc);
	}
}

void GameIOCurses::createGameWorldWindow(int lStartY, int lStartX, int lHeight, int lWidth)
{
	windowList.push_back(new CursesGameWorldWindow(lStartY, lStartX, lHeight, lWidth));
}

void GameIOCurses::addInputSource(IInputSource* lInputSource)
{
	inputList.push_back(static_cast<IInputSourceCurses*>(lInputSource));
}

void GameIOCurses::getInput(void)
{
	//if there are any input sources
	std::vector<IInputSourceCurses*>::iterator inIt(inputList.begin());
	if(inIt != inputList.end())
	{
		//grab the last keypress and process the source's input
		InputMessage* msg = (*inIt)->processInput(inputWindow->getInput());
		//determine the action to follow based on the output
		decipherMessage(msg);
		delete msg;
	}
}

void GameIOCurses::decipherMessage(InputMessage* lMsg)
{
	switch(lMsg->getType())
	{
	case NOMESSAGE:
		break;
	case OPENPAUSEMENU:
		break;
	}
}