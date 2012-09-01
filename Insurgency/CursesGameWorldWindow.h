#pragma once
#include "curseswindow.h"
#include "IGameWorld.h"
#include <map>
class CursesGameWorldWindow :
	public CursesWindow
{
public:
	CursesGameWorldWindow(int lStartY, int lStartX, int lHeight, int lWidth);
	virtual ~CursesGameWorldWindow(void);

	virtual void refWin(const IGameWorld& lGameWorld, std::pair<int,int> lCenterLoc);
};

