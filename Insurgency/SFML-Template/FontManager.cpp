#include "StdAfx.h"
#include "FontManager.h"

FontManager* s_FontManager = NULL;

FontManager::FontManager(void)
{
}


FontManager::~FontManager(void)
{
	clearFonts();
}

FontManager& FontManager::getInstance(void)
{
	if(s_FontManager == NULL)
	{
		s_FontManager = new FontManager();
	}
	return *s_FontManager;
}

const sf::Font& FontManager::getFont(const std::string& fontID)
{
	std::map<std::string, sf::Font*>::iterator fontIt(m_fonts.find(fontID));
	if(fontIt == m_fonts.end())
	{
		printf("FONT \"%s\" NOT FOUND\n", fontID.c_str());
		return sf::Font::getDefaultFont();
	}
		else
			return *(fontIt->second);
}

bool FontManager::addFont(sf::Font* font, const std::string& fontID)
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
	sf::Font* font = new sf::Font();
	if(font->loadFromFile(fileName))
	{
		if(!addFont(font, fontID)) //something bad happened, delete the font to prevent mem leak
		{
			printf("Failed to add \"%s\" to font manager\n", fileName.c_str());
			delete font;
			return false;
		}
	}
	return true;
}

void FontManager::removeFont(const std::string& fontID)
{
	std::map<std::string, sf::Font*>::iterator fontIt(m_fonts.find(fontID));
	if(fontIt == m_fonts.end())
		return;
	delete fontIt->second;
	m_fonts.erase(fontID);
}

void FontManager::clearFonts(void)
{
	for(std::map<std::string, sf::Font*>::iterator fontIt(m_fonts.begin()); fontIt != m_fonts.end(); fontIt++)
	{
		delete fontIt->second;
	}
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