#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
class SpriteManager
{
public:
	SpriteManager(void);
	~SpriteManager(void);

	static SpriteManager& getInstance();
	const sf::Sprite& getSprite(const std::string& spriteID) const;
	void addSprite(const sf::Sprite& sprite, const std::string& spriteID);

	void removeSprite(const std::string& spriteID);
	void clearSprites(void);

	static void cleanup(void);

private:
	std::map<std::string, sf::Sprite> m_sprites;
};

