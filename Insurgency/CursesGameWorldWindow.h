#pragma once
#include "curseswindow.h"
#include "GameWorld.h"
#include <map>
class CursesGameWorldWindow :
	public CursesWindow
{
public:
	CursesGameWorldWindow(int lStartY, int lStartX, int lHeight, int lWidth);
	virtual ~CursesGameWorldWindow(void);

	virtual void refWin(const GameWorld& lGameWorld, std::pair<int,int> lCenterLoc);
};

