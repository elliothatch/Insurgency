#pragma once
#include <vector>
#include "UIMenuOption.h"
class UIMenuList
{
public:
	UIMenuList(void);
	UIMenuList(std::vector<UIMenuOption*> options);
	virtual ~UIMenuList(void);

	void pushNewMenuOption(std::unique_ptr<UIMenuList> menuList, std::unique_ptr<UIMenuOption> listOption);
	void eraseMenuOption(unsigned int index);

	int m_selection;
	std::vector<UIMenuOption*> m_options;
	bool m_accessible;
private:
	//used for lists that make options dynamically
	std::vector<std::pair<std::unique_ptr<UIMenuList>, std::unique_ptr<UIMenuOption>>> m_optionStorage;
};

