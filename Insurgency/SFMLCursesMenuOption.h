#pragma once
#include <string>
class SFMLCursesMenuList;
class SFMLCursesMenuOption
{
public:
	SFMLCursesMenuOption(std::string name, SFMLCursesMenuList* target = nullptr, bool active = true);
	~SFMLCursesMenuOption(void);

	std::string m_name;
	std::string m_helpText;
	SFMLCursesMenuList* m_target;
	bool m_active;
	bool m_visited;
	bool m_hidden;
	int m_selectionStep;
	static const int TRUNK = 0;
	static const int EXIT_MENU = -1;
};
