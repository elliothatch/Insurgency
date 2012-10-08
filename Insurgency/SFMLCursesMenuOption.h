#pragma once
class SFMLCursesMenuList;
class SFMLCursesMenuOption
{
public:
	SFMLCursesMenuOption(void);
	~SFMLCursesMenuOption(void);

	SFMLCursesMenuList* target;
	bool active;
	int selectionStep;
	static const int TRUNK = 0;
	static const int EXIT_MENU = -1;
};
