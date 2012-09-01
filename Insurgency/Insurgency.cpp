// Insurgency.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameWorld.h"
#include "GameIOCurses.h"
#include "WorldTileTypeDef.h"
#include "GameItemTypeDef.h"
#include "CreatureTypeDef.h"
#include "GameTurnTimer.h"
#include "CreatureInputSourceCurses.h"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	//testing stuff
	{
	WorldTileTypeDef tileTypeDef;
	CreatureTypeDef creatureTypeDef;
	GameItemTypeDef itemTypeDef;
	GameWorld world(tileTypeDef, creatureTypeDef, itemTypeDef);
	GameTurnTimer turnTimer(world);
	world.test(std::pair<int,int>(-100,-100), std::pair<int,int>(100,100));
	world.setTile(std::pair<int,int>(0,0), new WorldTile(world.tileTypeDef.getTileType(128)));
	world.setTile(std::pair<int,int>(6,-3), new WorldTile(world.tileTypeDef.getTileType(128)));
	world.setTile(std::pair<int,int>(-2,-4), new WorldTile(world.tileTypeDef.getTileType(128)));
	
	world.createItem(1,std::pair<int,int>(0,0));
	std::vector<GameItem*>* itemPile = world.getItemPile(std::pair<int,int>(0,0));
	std::cout<<itemPile->at(0)->getLName()<<std::endl;
	std::cout<<itemPile->at(0)->getSName()<<std::endl;
	world.destroyItem(itemPile->at(0),std::pair<int,int>(0,0));

	world.createCreature(1,std::pair<int,int>(0,0));
	Creature* creature = world.getCreature(std::pair<int,int>(0,0));
	std::cout<<creature->getLName()<<std::endl;
	std::cout<<creature->getSName()<<std::endl;
	std::cout<<creature->getSpeed()<<std::endl;
	std::cout<<creature->getStrength()<<std::endl;
	world.destroyCreature(creature,std::pair<int,int>(0,0));
	std::system("PAUSE");
	/*
	world.lookupTile(std::pair<int,int>(0,0))->setType(world.tileTypeDef.getTileType(128));
	world.lookupTile(std::pair<int,int>(-5,-2))->setType(world.tileTypeDef.getTileType(64));
	world.lookupTile(std::pair<int,int>(1,6))->setType(world.tileTypeDef.getTileType(64));
	world.lookupTile(std::pair<int,int>(-3,4))->setType(world.tileTypeDef.getTileType(64));
	*/
	GameIOCurses gameIO;
	gameIO.createGameWorldWindow(1,1,20,20);
	gameIO.drawGameWorld(world,std::pair<int,int>(0,0));
	//std::cout<<world.lookupTile(std::pair<int,int>(5,5))->getTitle()<<std::endl;
	}
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
		#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
	_CrtDumpMemoryLeaks();
	system("PAUSE");
	return 0;
}

