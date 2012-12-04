#include "StdAfx.h"
#include "SFMLCursesCharManager.h"

SFMLCursesCharManager* s_SFMLCursesCharManager = nullptr;
const sf::Window* s_SFMLCursesCharManagerWindow;

SFMLCursesCharManager::SFMLCursesCharManager(const sf::Window& window)
	:m_window(window),
	 m_cursesChars()
{
}


SFMLCursesCharManager::~SFMLCursesCharManager(void)
{
}

void SFMLCursesCharManager::setWindow(const sf::Window& window)
{
	s_SFMLCursesCharManagerWindow = &window;
}

SFMLCursesCharManager& SFMLCursesCharManager::getInstance()
{
	if(s_SFMLCursesCharManager == NULL)
	{
		s_SFMLCursesCharManager = new SFMLCursesCharManager(*s_SFMLCursesCharManagerWindow);
		s_SFMLCursesCharManager->addCursesChar(SFMLCursesChar(s_SFMLCursesCharManager->m_window," ", sf::Color::Black, sf::Color::Magenta),
			 "CURSESCHARNOTFOUND");
	}
	return *s_SFMLCursesCharManager;
}
const SFMLCursesChar& SFMLCursesCharManager::getCursesChar(const std::string& cursesCharID) const
{
	std::map<std::string, SFMLCursesChar>::const_iterator cursesCharIt(m_cursesChars.find(cursesCharID));
	if(cursesCharIt == m_cursesChars.end())
	{
		printf("CURSESCHAR \"%s\" NOT FOUND\n", cursesCharID.c_str());
		return m_cursesChars.at("CURSESCHARNOTFOUND");
	}
		else
			return cursesCharIt->second;
}
void SFMLCursesCharManager::addCursesChar(const SFMLCursesChar& cursesChar, const std::string& cursesCharID)
{
	m_cursesChars.insert(std::make_pair<std::string,SFMLCursesChar>(cursesCharID, cursesChar));
}
void SFMLCursesCharManager::removeCursesChar(const std::string& cursesCharID)
{
	m_cursesChars.erase(cursesCharID);
}
void SFMLCursesCharManager::clearCursesChars(void)
{
	m_cursesChars.clear();
}

void SFMLCursesCharManager::cleanup(void)
{
	if(s_SFMLCursesCharManager != NULL)
	{
		delete s_SFMLCursesCharManager;
		s_SFMLCursesCharManager = NULL;
	}
}