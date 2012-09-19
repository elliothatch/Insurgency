// Insurgency.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SFMLApp.h"
#include <iostream>

int main(int argc, _TCHAR* argv[])
{
	//testing stuff
	{
		SFMLApp app;
		return app.OnExecute();
	}
		/*
	WorldTileTypeDef tileTypeDef;
	CreatureTypeDef creatureTypeDef;
	GameItemTypeDef itemTypeDef;
	GameWorld world(tileTypeDef, creatureTypeDef, itemTypeDef);
	GameTurnTimer turnTimer(world);
	world.test(std::pair<int,int>(-100,-100), std::pair<int,int>(100,100));
	WorldTile::ptr tile01(new WorldTile(world.m_tileTypeDef.getTileType(128)));
	WorldTile::ptr tile02(new WorldTile(world.m_tileTypeDef.getTileType(128)));
	WorldTile::ptr tile03(new WorldTile(world.m_tileTypeDef.getTileType(128)));

	world.setTile(std::pair<int,int>(0,0),std::move(tile01));
	world.setTile(std::pair<int,int>(6,-3),std::move(tile02));
	world.setTile(std::pair<int,int>(-2,-4),std::move(tile03));
	
	GameItem& item1(world.createItem(1));
	world.addItemToWorld(item1, std::pair<int,int>(0,0));
	std::vector<GameItem*>* itemPile = world.getItemPile(std::pair<int,int>(0,0));
	std::cout<<itemPile->at(0)->getLName()<<std::endl;
	std::cout<<itemPile->at(0)->getSName()<<std::endl;
	world.destroyItem(*itemPile->at(0));

	Creature& creature1(world.createCreature(1));
	world.addCreatureToWorld(creature1,std::pair<int,int>(0,0));
	Creature* creature = world.getCreature(std::pair<int,int>(0,0));
	std::cout<<creature->getLName()<<std::endl;
	std::cout<<creature->getSName()<<std::endl;
	std::cout<<creature->getSpeed()<<std::endl;
	std::cout<<creature->getStrength()<<std::endl;
	if(creature->getComponent(EntityComponentID::Inventory))
	{
		InventoryComponent* inventory(dynamic_cast<InventoryComponent*>(creature->getComponent(EntityComponentID::Inventory)));
		std::cout<<"Has Inventory Component\n";
		inventory->addEntity(item1);
		std::cout<<inventory->getNumEntities()<<std::endl;
	}
	if(creature->getComponent(EntityComponentID::Gun))
		std::cout<<"Has Gun Component\n";
	world.destroyCreature(*creature);
	std::system("PAUSE");
	*/
	/*
	world.lookupTile(std::pair<int,int>(0,0))->setType(world.tileTypeDef.getTileType(128));
	world.lookupTile(std::pair<int,int>(-5,-2))->setType(world.tileTypeDef.getTileType(64));
	world.lookupTile(std::pair<int,int>(1,6))->setType(world.tileTypeDef.getTileType(64));
	world.lookupTile(std::pair<int,int>(-3,4))->setType(world.tileTypeDef.getTileType(64));
	*/
	/*
	GameIOCurses gameIO;
	gameIO.createGameWorldWindow(1,1,20,20);
	gameIO.drawGameWorld(world,std::pair<int,int>(0,0));
	//std::cout<<world.lookupTile(std::pair<int,int>(5,5))->getTitle()<<std::endl;
	}
	*/
	/*
	WorldTileTypeDef tileTypeDef;
	CreatureTypeDef creatureTypeDef;
	GameItemTypeDef itemTypeDef;
	GameWorld world(tileTypeDef, creatureTypeDef, itemTypeDef);
	GameTurnTimer turnTimer(world);
	GameIOCurses gameIO;
	//place an creature input source for the player
	CreatureInputSourceCurses* playerCreatureInputSource = new CreatureInputSourceCurses();
	gameIO.addInputSource(playerCreatureInputSource);
	//main game loop
	while(true)
	{
		//get the creatures that can make an action this turn
		std::vector<Creature*> actingCreatures(turnTimer.getCreaturesCanMove());
		while(!actingCreatures.empty())
		{
			//get the last creature in the vector
			std::vector<Creature*>::iterator creatureIt(actingCreatures.end()--);
			//if that creature is the player, go into a player input loop (there are some cases where this gives the player an advantage over npcs)
			if((*creatureIt) == world.getPlayerCreature())
			{
				gameIO.processPlayerInput();
			}
			else
			{
				creatureAI.processCreatureTurn((*creatureIt));
			}
		}
	}
	*/
	/*
		#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
	_CrtDumpMemoryLeaks();
	system("PAUSE");
	*/
	//return 0;
}

