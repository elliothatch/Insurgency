#include "stdafx.h"
#include "SFMLApp.h"
#include <sstream>


bool SFMLApp::OnInit(void)
{
	m_mainWindow.create(sf::VideoMode(800, 600, 32), "SFMLApp Window");

	TextureManager& textureManager = TextureManager::getInstance();
	sf::Image cursesAImage;
	cursesAImage.loadFromFile("assets/graphics/curses_640x300.bmp");
	cursesAImage.createMaskFromColor(sf::Color::Magenta);
	textureManager.addTextureFromImage(cursesAImage,"CursesA");
	textureManager.getTexture("CursesA");
	SpriteManager& spriteManager = SpriteManager::getInstance();
	int k = 0;
	for(int i = 0; i < 16; i++)
	{
		for(int j = 0; j< 16; j++)
		{
			std::stringstream out;
			out << k;
			spriteManager.addSprite(sf::Sprite(textureManager.getTexture("CursesA"),sf::IntRect(j*8, i*12, 8, 12)),"CursesA_"+ out.str());
			k++;
		}
	}

	std::unique_ptr<GameState_InsurgencyGame> insurgencyGameState(new GameState_InsurgencyGame());
	registerState(std::move(insurgencyGameState), "InsurgencyGame");
	changeState("InsurgencyGame");

	return true;
}