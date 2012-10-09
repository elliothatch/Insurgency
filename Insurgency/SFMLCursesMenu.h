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
	SFMLCursesMenuList* m_previousMenuList;
	SFMLCursesMenuList* m_currentMenuList;
	SFMLCursesMenuList* m_nextMenuList;
	std::vector<SFMLCursesMenuList*> m_branch;
	int m_selection;
};

