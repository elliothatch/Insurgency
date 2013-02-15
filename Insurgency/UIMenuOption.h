#pragma once
#include <string>
class UIMenuList;
class UIMenuOption
{
public:
	UIMenuOption(const std::string& name, UIMenuList* target = nullptr, const std::string& tag = "", bool active = true);
	~UIMenuOption(void);

	std::string m_name;
	std::string m_helpText;
	std::string m_tag;
	UIMenuList* m_target;
	bool m_active;
	bool m_visited;
	bool m_hidden;
	int m_selectionStep;
	static const int TRUNK = 0;
	static const int EXIT_MENU = -1;
};
