#include "StdAfx.h"
#include "TextureManager.h"

TextureManager* s_TextureManager = NULL;
sf::Texture* s_TextureNotFound = NULL;

TextureManager::TextureManager(void)
{
}


TextureManager::~TextureManager(void)
{
	clearTextures();
}

TextureManager& TextureManager::getInstance(void)
{
	if(s_TextureManager == NULL)
	{
		s_TextureManager = new TextureManager();
		if(s_TextureNotFound == NULL)
		{
			s_TextureNotFound = new sf::Texture();
			s_TextureNotFound->create(64,64);
			sf::Image image;
			image.create(64,64,sf::Color::Magenta);
			s_TextureNotFound->loadFromImage(image);
			s_TextureManager->addTexture(s_TextureNotFound,"TEXTURENOTFOUND");
		}
	}
	return *s_TextureManager;
}

sf::Texture& TextureManager::getTexture(const std::string& textureID) const
{
	std::map<std::string, sf::Texture*>::const_iterator textureIt(m_textures.find(textureID));
	if(textureIt == m_textures.end())
	{
		printf("IMAGE \"%s\" NOT FOUND\n", textureID.c_str());
		return *s_TextureNotFound;
	}
		else
			return *(textureIt->second);
}

bool TextureManager::addTexture(sf::Texture* texture, const std::string& textureID)
{
	if(m_textures.size() > 0 && m_textures.find(textureID) != m_textures.end()) //there is already a texture by that name
	{
		printf("TEXTURE \"%s\" ALREADY REGISTERED\n", textureID.c_str());
		return false;
	}
	m_textures[textureID] = texture;
	return true;
}

bool TextureManager::addTextureFromFile(const std::string& fileName, const std::string& textureID)
{
	sf::Texture* texture = new sf::Texture();
	if(texture->loadFromFile(fileName))
	{
		if(!addTexture(texture, textureID)) //something bad happened, delete the texture to prevent mem leak
		{
			printf("Failed to add \"%s\" to manager\n", fileName.c_str());
			delete texture;
			return false;
		}
	}
	return true;
}

bool TextureManager::addTextureFromImage(const sf::Image& image, const std::string& textureID)
{
	sf::Texture* texture = new sf::Texture();
	if(texture->loadFromImage(image))
	{
		if(!addTexture(texture, textureID)) //something bad happened
		{
			printf("Failed to add image to manager\n");
			delete texture;
			return false;
		}
	}
	return true;
}

void TextureManager::removeTexture(const std::string& textureID)
{
	std::map<std::string, sf::Texture*>::iterator textureIt(m_textures.find(textureID));
	if(textureIt == m_textures.end())
		return;
	delete textureIt->second;
	m_textures.erase(textureIt);
}

void TextureManager::clearTextures(void)
{
	for(std::map<std::string, sf::Texture*>::iterator textureIt(m_textures.begin()); textureIt != m_textures.end(); textureIt++)
	{
		delete textureIt->second;
	}
	m_textures.clear();
}

void TextureManager::cleanup(void)
{
	if(s_TextureManager != NULL)
	{
		delete s_TextureManager;
		s_TextureManager = NULL;
	}
	s_TextureNotFound = NULL;
}