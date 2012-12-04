#pragma once
#include <SFML/Graphics.hpp>
class FontManager
{
protected:
	FontManager(void);
public:
	~FontManager(void);

	static FontManager& getInstance(void);
	sf::Font& getFont(const std::string& fontID);
	const sf::Font& getFont(const std::string& fontID) const;
	bool addFont(const sf::Font& font, const std::string& fontID);
	bool addFontFromFile(const std::string& fileName, const std::string& fontID);

	void removeFont(const std::string& fontID);
	void clearFonts(void);

	static void cleanup(void);

private:
	std::map<std::string, sf::Font> m_fonts;
};

