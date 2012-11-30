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
	virtual void executeSelection() = 0;
	virtual void changeSelection();
	void update();

private:
	UIMenuList* m_previousMenuList;
	UIMenuList* m_currentMenuList;
	UIMenuList* m_nextMenuList;
	std::vector<UIMenuList*> m_branch;
	int m_selection;
	std::string m_helpText;
	bool m_hideChangeSelection;
};

