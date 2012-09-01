#pragma once
#include <curses.h>
#include "colorListCurses.h"
class CursesWindow
{
public:
	CursesWindow(int lStartY, int lStartX, int lHeight, int lWidth);
	virtual ~CursesWindow(void);

	virtual void refWin(void) {wrefresh(main);} //redraw window
	virtual void update(void) {} //update contents
	int getY(void) {return y;}
	int getX(void) {return x;}
	int getHeight(void) {return height;}
	int getWidth(void) {return width;}
	chtype getInput(void) {return wgetch(main);}
	//should the IO class be able to directly modify the window?
	//no.
	virtual WINDOW* getWindow(void) {return main;}
	//setters
	void setKeypad(bool b) {keypad(main, b);}
	void setInputTimeout(int num) {wtimeout(main, num);}

	void setCharFGColor(int lY, int lX, CursesColor lColor);
	void setCharBGColor(int lY, int lX, CursesColor lColor);

	void addChar(chtype lChar) {waddch(main, lChar);}
	void addChar(chtype lChar, int y, int x) {mvwaddch(main,y,x,lChar);}
	
protected:
	WINDOW* main;
	int y;
	int x;
	int width;
	int height;
};

inline void CursesWindow::setCharFGColor(int lY, int lX, CursesColor lColor)
{
	if(!(lY < 0 || lY > height || lX < 0 || lX > width)) //if the coordinates are valid
	{
		//get old char and color
		chtype oldChar = mvwinch(main, lY, lX);
		chtype oldColor = oldChar & A_COLOR;
		//convert into pair notation
		std::pair<CursesColor,CursesColor> colors(CursesColorList::getSeperateColors(CursesColorPair(PAIR_NUMBER(oldColor))));
		CursesColorPair newPair = CursesColorList::makeColorPair(lColor, colors.second);
		//print the new char with correct color
		mvwaddch(main, lY, lX, (oldChar & A_CHARTEXT) | COLOR_PAIR(newPair));
	}
}

inline void CursesWindow::setCharBGColor(int lY, int lX, CursesColor lColor)
{
	if(!(lY < 0 || lY > height || lX < 0 || lX > width)) //if the coordinates are valid
	{
		//get old char and color
		chtype oldChar = mvwinch(main, lY, lX);
		chtype oldColor = oldChar & A_COLOR;
		//convert into pair notation
		std::pair<CursesColor,CursesColor> colors(CursesColorList::getSeperateColors(CursesColorPair(PAIR_NUMBER(oldColor))));
		CursesColorPair newPair = CursesColorList::makeColorPair(colors.first, lColor);
		//print the new char with correct color
		mvwaddch(main, lY, lX, (oldChar & A_CHARTEXT) | COLOR_PAIR(newPair));
	}
}