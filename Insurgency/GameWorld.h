#pragma once
#include "IWorldTileTypeDef.h"
#include "ICreatureTypeDef.h"
#include "IGameItemTypeDef.h"
#include "GameItem.h"
#include "Creature.h"
#include "WorldRegion.h"
#include "WorldTile.h"
#include <map>
#include <algorithm>
class GameWorld
{
public:
	GameWorld(const IWorldTileTypeDef& lWorldTileTypeDef,
			  const ICreatureTypeDef& lCreatureTypeDef,
			  const IGameItemTypeDef& lGameItemTypeDef);
	~GameWorld(void);
	
	void addItem(GameItem* lGameItem, std::pair<int,int> loc);	  //DOES NOT CREATE ITEM
	void removeItem(GameItem* lGameItem, std::pair<int,int> loc); //DOES NOT DELETE ITEM
	void addCreature(Creature* lCreature, std::pair<int,int> loc); //does not create creature
	void removeCreature(Creature* lCreature, std::pair<int,int> loc); //does not delete creature

	//create/destroy
	void createItem(GameItemTypeID lTypeID, std::pair<int,int> loc);
	void destroyItem(GameItem* lGameItem, std::pair<int,int> loc);
	void createCreature(CreatureTypeID lTypeID, std::pair<int,int> loc);
	void destroyCreature(Creature* lCreature, std::pair<int,int> loc);

	//get entities
	std::vector<GameItem*>* getItemPile(std::pair<int,int> loc) const;
	Creature* getCreature(std::pair<int,int> loc) const;

	std::vector<Creature*> getCreatureList(void) const;
	
	Creature* getPlayerCreature(void) const;
	void setPlayerCreature(Creature* lCreature);

	//events in the world
	void moveGameItem(GameItem* lGameItem, std::pair<int,int> loc);
	bool moveCreature(Creature* lCreature, std::pair<int,int> loc);
	
	//public for testing
	WorldTile* lookupTile(std::pair<int,int> loc) const;
	void setTile(std::pair<int,int> loc, WorldTile* lTile); //assumes the region exists
	//testing
	void test(std::pair<int,int> point1, std::pair<int,int> point2){fillArea(point1, point2);}
private:
	void fillArea(std::pair<int,int> point1, std::pair<int,int> point2);
	std::pair<int,int> lookupRegion(std::pair<int,int> loc) const;
	std::pair<int,int> lookupRegionTilePos(std::pair<int,int> loc) const;

	//members
	//tile type definitions
	//public for test
public:
	const IWorldTileTypeDef& tileTypeDef;
	const ICreatureTypeDef& creatureTypeDef;
	const IGameItemTypeDef& itemTypeDef;
private:

	std::map<std::pair<int,int>,std::vector<GameItem*>> gameItemCoord;
	//this vector is useful for iterating through turns... probably can just do that from the map.
	//std::vector<Creature*> creatureList;
	std::map<std::pair<int,int>,Creature*> creatureCoord;
	std::map<std::pair<int,int>, WorldRegion*> regionCoord;
	//special pointer to the player's creature
	Creature* playerCreature;
};

