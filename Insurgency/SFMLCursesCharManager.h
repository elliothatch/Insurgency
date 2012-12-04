#pragma once
#include <map>
#include <functional>
#include "SFMLCursesChar.h"
class SFMLCursesCharManager
{
public:
	SFMLCursesCharManager(const sf::Window& window);
	~SFMLCursesCharManager(void);

	static void setWindow(const sf::Window& window);
	static SFMLCursesCharManager& getInstance();
	const SFMLCursesChar& getCursesChar(const std::string& cursesCharID) const;
	void addCursesChar(const SFMLCursesChar& cursesChar, const std::string& cursesCharID);

	void removeCursesChar(const std::string& cursesCharID);
	void clearCursesChars(void);

	static void cleanup(void);

private:
	std::reference_wrapper<const sf::Window> m_window;
	std::map<std::string, SFMLCursesChar> m_cursesChars;
};

