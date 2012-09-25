#include "stdafx.h"
#include "SFMLApp.h"
#include <sstream>


bool SFMLApp::OnInit(void)
{
	m_mainWindow.create(sf::VideoMode(800, 600, 32), "Insurgency");

	TextureManager& textureManager = TextureManager::getInstance();
	sf::Image cursesAImage;
	cursesAImage.loadFromFile("assets/graphics/curses_640x300.bmp");
	cursesAImage.createMaskFromColor(sf::Color::Magenta);
	textureManager.addTextureFromImage(cursesAImage,"CursesA");
	const sf::Texture& cursesA = textureManager.getTexture("CursesA");
	SpriteManager& spriteManager = SpriteManager::getInstance();
	char k = 0;
	for(int i = 0; i < 16; i++)
	{
		for(int j = 0; j< 16; j++)
		{
			std::string str("CursesA_ASCII");
			str += k;
			spriteManager.addSprite(sf::Sprite(textureManager.getTexture("CursesA"),sf::IntRect(j*8, i*12, 8, 12)),str);
			k++;
		}
	}
	sf::Sprite dirtground(cursesA, sf::IntRect(14*8,2*12,8,12));
	dirtground.setColor(sf::Color(130,54,21,255));
	spriteManager.addSprite(dirtground,"CursesA_dirt ground");
	sf::Sprite dirtwall(cursesA, sf::IntRect(3*8,2*12,8,12));
	dirtwall.setColor(sf::Color(173,74,21,255));
	spriteManager.addSprite(dirtwall,"CursesA_dirt wall");
	sf::Sprite concretewall(cursesA, sf::IntRect(3*8,2*12,8,12));
	concretewall.setColor(sf::Color(150,150,150,255));
	spriteManager.addSprite(concretewall,"CursesA_concrete wall");
	sf::Sprite insurgent(cursesA, sf::IntRect(0,4*12,8,12));
	spriteManager.addSprite(insurgent, "CursesA_insurgent");
	sf::Sprite ak47(cursesA, sf::IntRect(8*8,2*12,8,12));
	ak47.setColor(sf::Color(255,100,100,255));
	spriteManager.addSprite(ak47, "CursesA_AK-47");
	sf::Sprite p90(cursesA, sf::IntRect(8*8,2*12,8,12));
	p90.setColor(sf::Color(100,100,255,255));
	spriteManager.addSprite(p90, "CursesA_P90");

	std::unique_ptr<GameState_InsurgencyGame> insurgencyGameState(new GameState_InsurgencyGame());
	registerState(std::move(insurgencyGameState), "InsurgencyGame");
	std::unique_ptr<GameState_InsurgencyInventory> insurgencyInventoryState(new GameState_InsurgencyInventory());
	registerState(std::move(insurgencyInventoryState), "InsurgencyInventory");
	changeState("InsurgencyGame", nullptr);

	return true;
}