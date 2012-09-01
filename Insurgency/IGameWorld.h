#pragma once
#include <vector>
//#include "IWorldRegion.h"
#include "IWorldTileTypeDef.h"
#include "IGameItemTypeDef.h"
#include "GameItemType.h"
#include "IWorldTile.h"
#include "GameEntity.h"
#include "GameItem.h"
#include "Creature.h"
#include "ICreatureTypeDef.h"
#include "EntityComponent.h"
//replace the above include with a header file storing all the entity components
class IGameWorld
{
public:

	IGameWorld(const IWorldTileTypeDef& lWorldTileTypeDef,
			   const ICreatureTypeDef& lCreatureTypeDef,
			   const IGameItemTypeDef& lGameItemTypeDef)
	{
	}

	virtual ~IGameWorld(void)
	{
	}
	//do not create or destroy entities
	//remove?
	virtual void addItem(GameItem* lGameItem, std::pair<int,int> loc) = 0;
	virtual void removeItem(GameItem* lGameItem, std::pair<int,int> loc) = 0;
	virtual void addCreature(Creature* lCreature, std::pair<int,int> loc) = 0;
	virtual void removeCreature(Creature* lCreature, std::pair<int,int> loc) = 0;
	//allocates and creates/destroys entities
	virtual void createItem(GameItemTypeID lTypeID, std::pair<int,int> loc) = 0;
	virtual void destroyItem(GameItem* lGameItem, std::pair<int,int> loc) = 0;
	virtual void createCreature(CreatureTypeID ltypeID, std::pair<int,int> loc) = 0;
	virtual void destroyCreature(Creature* lCreature, std::pair<int,int> loc) = 0;

	virtual std::vector<GameItem*>* getItemPile(std::pair<int,int> loc) const = 0;
	virtual Creature* getCreature(std::pair<int,int> loc) const = 0;

	virtual std::vector<Creature*> getCreatureList(void) const = 0;

	virtual bool moveCreature(Creature* lCreature, std::pair<int,int> loc) = 0;
	virtual void moveGameItem(GameItem* lGameItem, std::pair<int,int> loc) = 0;
	virtual IWorldTile* lookupTile(std::pair<int,int> loc) const = 0;
	virtual void setTile(std::pair<int,int> loc, IWorldTile* lTile) = 0;

	virtual void setPlayerCreature(Creature* lCreature) = 0;
	virtual Creature* getPlayerCreature(void) const = 0;
};

