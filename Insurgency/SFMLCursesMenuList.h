#pragma once
#include <vector>
#include "SFMLCursesMenuOption.h"
class SFMLCursesMenuList
{
public:
	SFMLCursesMenuList(void);
	SFMLCursesMenuList(std::vector<SFMLCursesMenuOption*> options);
	~SFMLCursesMenuList(void);

	int m_selection;
	std::vector<SFMLCursesMenuOption*> m_options;
	bool m_accessible;
};

