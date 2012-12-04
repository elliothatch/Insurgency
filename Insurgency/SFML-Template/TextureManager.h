#pragma once
#include <SFML/Graphics.hpp>
#include <map>
class TextureManager
{
protected:
	TextureManager(void);
public:
	~TextureManager(void);

	static TextureManager& getInstance(void);
	sf::Texture& getTexture(const std::string& textureID);
	const sf::Texture& getTexture(const std::string& textureID) const;
	bool addTexture(const sf::Texture& texture, const std::string& textureID);
	bool addTextureFromFile(const std::string& fileName, const std::string& textureID);
	bool addTextureFromImage(const sf::Image& image, const std::string& textureID);

	void removeTexture(const std::string& textureID);
	void clearTextures(void);

	static void cleanup(void);

private:
	std::map<std::string, sf::Texture> m_textures;
};

