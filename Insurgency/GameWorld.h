#pragma once
#include "IWorldTileTypeDef.h"
#include "ICreatureTypeDef.h"
#include "IGameItemTypeDef.h"
#include "GameItem.h"
#include "Creature.h"
#include "EquipSlotsComponent.h"
#include "WorldRegion.h"
#include "WorldTile.h"
#include <map>
#include <set>
#include <algorithm>
class GameWorld
{
public:
	GameWorld(const IWorldTileTypeDef& lWorldTileTypeDef,
			  const ICreatureTypeDef& lCreatureTypeDef,
			  const IGameItemTypeDef& lGameItemTypeDef);
	~GameWorld(void);
	
	void addItemToWorld(GameItem& lGameItem, std::pair<int,int> loc);	  //DOES NOT CREATE ITEM
	void removeItemFromWorld(GameItem& lGameItem); //DOES NOT DELETE ITEM
	void addCreatureToWorld(Creature& lCreature, std::pair<int,int> loc); //does not create creature
	void removeCreatureFromWorld(Creature& lCreature); //does not delete creature

	//create/destroy
	GameItem& createItem(GameItemTypeID lTypeID);
	void destroyItem(GameItem& lGameItem);
	Creature& createCreature(CreatureTypeID lTypeID);
	void destroyCreature(Creature& lCreature);

	//get entities
	std::vector<GameItem*>* getItemPile(std::pair<int,int> loc) const;
	Creature* getCreature(std::pair<int,int> loc) const;

	std::set<Creature::ptr>& getCreatureSet(void) const;
	
	Creature* getPlayerCreature(void) const;
	void setPlayerCreature(Creature& lCreature);

	//events in the world
	void moveGameItem(GameItem& lGameItem, std::pair<int,int> loc);
	bool moveCreature(Creature& lCreature, std::pair<int,int> loc);
	bool putEntityInInventory(InventoryComponent& lContainer, GameEntity& lTarget);
	bool removeEntityFromInventory(InventoryComponent& lContainer, GameEntity& lTarget);

	bool entityEquipEntity(GameEntity& holder, GameEntity& target, const GameEntityEquipGroups::EquipGroup& equipGroup);
	bool entityUnequipEntity(GameEntity& holder, GameEntity& target);

	//public for testing
	WorldTile& lookupTile(std::pair<int,int> loc) const;
	void setTile(std::pair<int,int> loc, WorldTile::ptr lTile); //assumes the region exists
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
	const IWorldTileTypeDef* m_tileTypeDef;    //const
	const ICreatureTypeDef* m_creatureTypeDef; //const
	const IGameItemTypeDef* m_itemTypeDef;     //const
private:
	std::map<std::pair<int,int>, WorldRegion::ptr> m_regionCoord;

	//hold the items, regardless of if they are on the map, held by a creature, etc.
	std::set<GameItem::ptr> m_gameItems;
	std::set<Creature::ptr> m_creatures;

	std::map<std::pair<int,int>,std::vector<GameItem*>> m_gameItemCoord;
	std::map<std::pair<int,int>,Creature*> m_creatureCoord;


	//special pointer to the player's creature
	Creature* m_playerCreature;
};

