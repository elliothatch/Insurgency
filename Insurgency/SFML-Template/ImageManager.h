#pragma once
#include <SFML/Graphics.hpp>
#include <map>
class ImageManager
{
protected:
	ImageManager(void);
public:
	~ImageManager(void);

	static ImageManager& getInstance(void);
	sf::Image& getImage(const std::string& imageID);
	const sf::Image& getImage(const std::string& imageID) const;
	bool addImage(const sf::Image& image, const std::string& imageID);
	bool addImageFromFile(const std::string& fileName, const std::string& imageID);

	void removeImage(const std::string& imageID);
	void clearImages(void);

	static void cleanup(void);

private:
	std::map<std::string, sf::Image> m_images;
};