#pragma once
#include <vector>
#include "SFMLCursesMenuList.h"
class SFMLCursesMenu
{
public:
	SFMLCursesMenu(void);
	virtual ~SFMLCursesMenu(void);

	void setTrunk(SFMLCursesMenuList* menuList);
	void select(int n);
	void stepRight();
	void stepLeft();
	virtual void executeSelection() = 0;
	void update();

private:
	SFMLCursesMenuList* previousMenuList;
	SFMLCursesMenuList* currentMenuList;
	SFMLCursesMenuList* nextMenuList;
	std::vector<SFMLCursesMenuList*> branch;
	int selection;
};

