#pragma once
#include <vector>
#include "UIMenuOption.h"
class UIMenuList
{
public:
	UIMenuList(void);
	UIMenuList(std::vector<UIMenuOption*> options);
	virtual ~UIMenuList(void);

	int m_selection;
	std::vector<UIMenuOption*> m_options;
	bool m_accessible;
};

