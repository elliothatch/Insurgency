#pragma once
#include <string>
class UIMenuList;
class UIMenuOption
{
public:
	UIMenuOption(std::string name, UIMenuList* target = nullptr, bool active = true);
	~UIMenuOption(void);

	std::string m_name;
	std::string m_helpText;
	UIMenuList* m_target;
	bool m_active;
	bool m_visited;
	bool m_hidden;
	int m_selectionStep;
	static const int TRUNK = 0;
	static const int EXIT_MENU = -1;
};
