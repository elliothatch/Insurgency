#pragma once
#include <vector>
#include "UIMenuList.h"
class UIMenu
{
public:
	UIMenu(void);
	virtual ~UIMenu(void);

	void setTrunk(UIMenuList* menuList);
	void select(int n);
	void stepRight();
	void stepLeft();
	virtual int executeSelection() = 0;
	virtual void changeSelection();
	void update();

	UIMenuList* m_previousMenuList;
	UIMenuList* m_currentMenuList;
	UIMenuList* m_nextMenuList;
	std::vector<UIMenuList*> m_branch;
	std::string m_helpText;
	int m_selection;
	bool m_hideChangeSelection;
};

