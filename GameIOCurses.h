#pragma once
#include "igameoutput.h"
#include "IGameInput.h"
#include "CursesGameWorldWindow.h"
#include "IInputSourceCurses.h"
#include <curses.h>
#include <vector>
class GameIOCurses :
	public IGameOutput,
	public IGameInput
{
public:
	GameIOCurses(void);
	virtual ~GameIOCurses(void);

	//output
	virtual void drawGameWorld(const IGameWorld& lWorld, std::pair<int,int> lCenterLoc);
	void createGameWorldWindow(int lStartY, int lStartX, int lHeight, int lWidth);

	//input
	virtual void addInputSource(IInputSource* lInputSource);
	virtual void getInput(void);
private:
	virtual void decipherMessage(InputMessage* lMsg);

private:

	std::vector<CursesWindow*> windowList;
	//static input window
	CursesWindow* inputWindow;
	//input source list
	std::vector<IInputSourceCurses*> inputList;
};

