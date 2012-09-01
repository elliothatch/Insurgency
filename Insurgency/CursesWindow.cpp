#include "StdAfx.h"
#include "CursesWindow.h"


CursesWindow::CursesWindow(int lStartY, int lStartX, int lHeight, int lWidth)
	:y(lStartY),
	 x(lStartX),
	 height(lHeight),
	 width(lWidth)
{
	main = newwin(lHeight,lWidth,lStartY,lStartX);
}


CursesWindow::~CursesWindow(void)
{
	delwin(main);
}
