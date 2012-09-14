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
	const sf::Texture& cursesA = textureManager.getTexture("CursesA");
	SpriteManager& spriteManager = SpriteManager::getInstance();
	/*
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
	*/
	sf::Sprite dirtground(cursesA, sf::IntRect(14*8,2*12,8,12));
	dirtground.setColor(sf::Color(130,54,21,255));
	spriteManager.addSprite(dirtground,"CursesA_dirt ground");
	sf::Sprite dirtwall(cursesA, sf::IntRect(3*8,2*12,8,12));
	dirtwall.setColor(sf::Color(173,74,21,255));
	spriteManager.addSprite(dirtwall,"CursesA_dirt wall");
	sf::Sprite concretewall(cursesA, sf::IntRect(3*8,2*12,8,12));
	concretewall.setColor(sf::Color(150,150,150,255));
	spriteManager.addSprite(concretewall,"CursesA_concrete wall");

	std::unique_ptr<GameState_InsurgencyGame> insurgencyGameState(new GameState_InsurgencyGame());
	registerState(std::move(insurgencyGameState), "InsurgencyGame");
	changeState("InsurgencyGame");

	return true;
}