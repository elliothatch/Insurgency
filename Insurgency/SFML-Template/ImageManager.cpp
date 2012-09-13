#include "StdAfx.h"
#include "ImageManager.h"

ImageManager* s_ImageManager = NULL;
sf::Image* s_ImageNotFound = NULL;

ImageManager::ImageManager(void)
{

}


ImageManager::~ImageManager(void)
{
	clearImages();
}

ImageManager& ImageManager::getInstance(void)
{
	if(s_ImageManager == NULL)
	{
		s_ImageManager = new ImageManager();
		if(s_ImageNotFound == NULL)
		{
			s_ImageNotFound = new sf::Image();
			s_ImageNotFound->create(64,64, sf::Color::Magenta);
		}

	}
	return *s_ImageManager;
}

sf::Image& ImageManager::getImage(const std::string& imageID)
{
	std::map<std::string, sf::Image*>::iterator imageIt(m_images.find(imageID));
	if(imageIt == m_images.end())
	{
		printf("IMAGE \"%s\" NOT FOUND\n", imageID.c_str());
		return *s_ImageNotFound;
	}
		else
			return *(imageIt->second);
}

bool ImageManager::addImage(sf::Image* image, const std::string& imageID)
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
	sf::Image* image = new sf::Image();
	if(image->loadFromFile(fileName))
	{
		if(!addImage(image, imageID)) //something bad happened, delete the image to prevent mem leak
		{
			printf("Failed to add \"%s\" to image manager\n", fileName.c_str());
			delete image;
			return false;
		}
	}
	return true;
}

void ImageManager::removeImage(const std::string& imageID)
{
	std::map<std::string, sf::Image*>::iterator imageIt(m_images.find(imageID));
	if(imageIt == m_images.end())
		return;
	delete imageIt->second;
	m_images.erase(imageID);
}

void ImageManager::clearImages(void)
{
	for(std::map<std::string, sf::Image*>::iterator imageIt(m_images.begin()); imageIt != m_images.end(); imageIt++)
	{
		delete imageIt->second;
	}
	m_images.clear();
}

void ImageManager::cleanup(void)
{
	if(s_ImageManager != NULL)
	{
		delete s_ImageManager;
		s_ImageManager = NULL;
	}
	if(s_ImageNotFound != NULL)
	{
		delete s_ImageNotFound;
		s_ImageNotFound = NULL;
	}
}