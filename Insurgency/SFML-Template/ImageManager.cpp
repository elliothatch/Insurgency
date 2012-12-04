#include "StdAfx.h"
#include "ImageManager.h"

ImageManager* s_ImageManager = NULL;

ImageManager::ImageManager(void)
{
}

ImageManager::~ImageManager(void)
{
}

ImageManager& ImageManager::getInstance(void)
{
	if(s_ImageManager == NULL)
	{
		s_ImageManager = new ImageManager();
		sf::Image imageNotFound;
		imageNotFound.create(64,64, sf::Color::Magenta);
		s_ImageManager->addImage(imageNotFound, "IMAGENOTFOUND");
	}
	return *s_ImageManager;
}

sf::Image& ImageManager::getImage(const std::string& imageID)
{
	std::map<std::string, sf::Image>::iterator imageIt(m_images.find(imageID));
	if(imageIt == m_images.end())
	{
		printf("IMAGE \"%s\" NOT FOUND\n", imageID.c_str());
		return m_images.at("IMAGENOTFOUND");
	}
		else
			return imageIt->second;
}
const sf::Image& ImageManager::getImage(const std::string& imageID) const
{
	std::map<std::string, sf::Image>::const_iterator imageIt(m_images.find(imageID));
	if(imageIt == m_images.end())
	{
		printf("IMAGE \"%s\" NOT FOUND\n", imageID.c_str());
		return m_images.at("IMAGENOTFOUND");
	}
		else
			return imageIt->second;
}

bool ImageManager::addImage(const sf::Image& image, const std::string& imageID)
{
	if(m_images.size() > 0 && m_images.find(imageID) != m_images.end()) //there is already an image by that name
	{
		printf("IMAGE \"%s\" ALREADY REGISTERED\n", imageID.c_str());
		return false;
	}
	m_images[imageID] = image;
	return true;
}

bool ImageManager::addImageFromFile(const std::string& fileName, const std::string& imageID)
{
	sf::Image image;
	if(image.loadFromFile(fileName))
	{
		if(!addImage(image, imageID)) //something bad happened
		{
			printf("Failed to add \"%s\" to image manager\n", fileName.c_str());
			return false;
		}
	}
	return true;
}

void ImageManager::removeImage(const std::string& imageID)
{
	std::map<std::string, sf::Image>::iterator imageIt(m_images.find(imageID));
	if(imageIt == m_images.end())
		return;
	m_images.erase(imageID);
}

void ImageManager::clearImages(void)
{
	m_images.clear();
}

void ImageManager::cleanup(void)
{
	if(s_ImageManager != NULL)
	{
		delete s_ImageManager;
		s_ImageManager = NULL;
	}
}