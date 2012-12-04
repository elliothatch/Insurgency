#include "StdAfx.h"
#include "FontManager.h"

FontManager* s_FontManager = NULL;

FontManager::FontManager(void)
{
}


FontManager::~FontManager(void)
{
}

FontManager& FontManager::getInstance(void)
{
	if(s_FontManager == NULL)
	{
		s_FontManager = new FontManager();
		sf::Font fontNotFound;
		fontNotFound = sf::Font::getDefaultFont();
		s_FontManager->addFont(fontNotFound, "FONTNOTFOUND");
	}
	return *s_FontManager;
}

sf::Font& FontManager::getFont(const std::string& fontID)
{
	std::map<std::string, sf::Font>::iterator fontIt(m_fonts.find(fontID));
	if(fontIt == m_fonts.end())
	{
		printf("FONT \"%s\" NOT FOUND\n", fontID.c_str());
		return m_fonts.at("FONTNOTFOUND");
	}
		else
			return fontIt->second;
}

const sf::Font& FontManager::getFont(const std::string& fontID) const
{
	std::map<std::string, sf::Font>::const_iterator fontIt(m_fonts.find(fontID));
	if(fontIt == m_fonts.end())
	{
		printf("FONT \"%s\" NOT FOUND\n", fontID.c_str());
		return m_fonts.at("FONTNOTFOUND");
	}
		else
			return fontIt->second;
}

bool FontManager::addFont(const sf::Font& font, const std::string& fontID)
{
	if(m_fonts.size() > 0 && m_fonts.find(fontID) != m_fonts.end()) //there is already an font by that name
	{
		printf("FONT \"%s\" ALREADY REGISTERED\n", fontID.c_str());
		return false;
	}
	m_fonts[fontID] = font;
	return true;
}

bool FontManager::addFontFromFile(const std::string& fileName, const std::string& fontID)
{
	sf::Font font;
	if(font.loadFromFile(fileName))
	{
		if(!addFont(font, fontID))
		{
			printf("Failed to add \"%s\" to font manager\n", fileName.c_str());
			return false;
		}
	}
	return true;
}

void FontManager::removeFont(const std::string& fontID)
{
	std::map<std::string, sf::Font>::iterator fontIt(m_fonts.find(fontID));
	if(fontIt == m_fonts.end())
		return;
	m_fonts.erase(fontID);
}

void FontManager::clearFonts(void)
{
	m_fonts.clear();
}

void FontManager::cleanup(void)
{
	if(s_FontManager != NULL)
	{
		delete s_FontManager;
		s_FontManager = NULL;
	}
}