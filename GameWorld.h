#pragma once
#include "igameworld.h"
#include "WorldRegion.h"
#include "IWorldTile.h"
#include <map>
#include <algorithm>
class GameWorld :
	public IGameWorld
{
public:
	GameWorld(const IWorldTileTypeDef& lWorldTileTypeDef,
			  const ICreatureTypeDef& lCreatureTypeDef,
			  const IGameItemTypeDef& lGameItemTypeDef);
	virtual ~GameWorld(void);
	
	virtual void addItem(GameItem* lGameItem, std::pair<int,int> loc);	  //DOES NOT CREATE ITEM
	virtual void removeItem(GameItem* lGameItem, std::pair<int,int> loc); //DOES NOT DELETE ITEM
	virtual void addCreature(Creature* lCreature, std::pair<int,int> loc); //does not create creature
	virtual void removeCreature(Creature* lCreature, std::pair<int,int> loc); //does not delete creature
	//create/destroy
	
	virtual void createItem(GameItemTypeID lTypeID, std::pair<int,int> loc);
	virtual void destroyItem(GameItem* lGameItem, std::pair<int,int> loc);
	virtual void createCreature(CreatureTypeID lTypeID, std::pair<int,int> loc);
	virtual void destroyCreature(Creature* lCreature, std::pair<int,int> loc);

	virtual std::vector<GameItem*>* getItemPile(std::pair<int,int> loc) const;
	virtual Creature* getCreature(std::pair<int,int> loc) const;

	virtual std::vector<Creature*> getCreatureList(void) const;

	virtual void setPlayerCreature(Creature* lCreature);
	virtual Creature* getPlayerCreature(void) const;

	//events in the world
	virtual bool moveCreature(Creature* lCreature, std::pair<int,int> loc);
	virtual void moveGameItem(GameItem* lGameItem, std::pair<int,int> loc);
private:

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
	std::map<std::pair<int,int>, IWorldRegion*> regionCoord;

	//special pointer to the player's creature
	Creature* playerCreature;

	void fillArea(std::pair<int,int> point1, std::pair<int,int> point2);

	std::pair<int,int> lookupRegion(std::pair<int,int> loc) const 
	{
		return std::pair<int,int>  (int(floor(float(loc.first)/float(REGIONSIZE))),
									int(floor(float(loc.second)/float(REGIONSIZE))));}
	std::pair<int,int> lookupRegionTilePos(std::pair<int,int> loc) const;
	//public for testing
public:
	virtual IWorldTile* lookupTile(std::pair<int,int> loc) const;
	virtual void setTile(std::pair<int,int> loc, IWorldTile* lTile); //assumes the region exists

	//testing
	void test(std::pair<int,int> point1, std::pair<int,int> point2){fillArea(point1, point2);}
};

