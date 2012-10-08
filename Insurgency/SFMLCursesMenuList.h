#pragma once
#include <vector>
#include "SFMLCursesMenuOption.h"
class SFMLCursesMenuList
{
public:
	SFMLCursesMenuList(void);
	~SFMLCursesMenuList(void);

	int selection;
	std::vector<SFMLCursesMenuOption*> options;
	bool accessible;
};

