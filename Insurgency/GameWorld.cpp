#include "StdAfx.h"
#include "GameWorld.h"


GameWorld::GameWorld(const IWorldTileTypeDef& lWorldTileTypeDef,
					 const ICreatureTypeDef& lCreatureTypeDef,
					 const IGameItemTypeDef& lGameItemTypeDef)
	:tileTypeDef(lWorldTileTypeDef),
	 creatureTypeDef(lCreatureTypeDef),
	 itemTypeDef(lGameItemTypeDef)
{
	
}
GameWorld::~GameWorld(void)
{
	//delete items in map
	for(std::map<std::pair<int,int>,std::vector<GameItem*>>::iterator pileIt = gameItemCoord.begin();
		pileIt != gameItemCoord.end(); pileIt++)
	{
		for(std::vector<GameItem*>::iterator itemIt = pileIt->second.begin(); itemIt != pileIt->second.end(); itemIt++)
		{
			delete (*itemIt);
		}
	}
	//delete creatures in map
	for(std::map<std::pair<int,int>, Creature*>::iterator creatureIt = creatureCoord.begin();
		creatureIt != creatureCoord.end(); creatureIt++)
	{
		//first remove their components
		for(int i = 0; i<creatureIt->second->getNumComponents(); i++)
		{
			delete creatureIt->second->getComponent(EntityComponentID(i));
		}
		delete creatureIt->second;
	}
	//delete World Regions
	for(std::map<std::pair<int,int>, WorldRegion*>::iterator regIt = regionCoord.begin(); regIt != regionCoord.end(); regIt++)
	{
		delete regIt->second;
	}
}
std::pair<int,int> GameWorld::lookupRegionTilePos(std::pair<int,int> loc) const
{	
	std::pair<int,int> tileLoc;
	//xcoord
	if(loc.first>=0)
		tileLoc.first=loc.first%REGIONSIZE;
	else
		tileLoc.first=REGIONSIZE+loc.first%REGIONSIZE;
	if(tileLoc.first==REGIONSIZE)
		tileLoc.first=0;
	//y coord
	if(loc.second>=0)
		tileLoc.second=loc.second%REGIONSIZE;
	else
		tileLoc.second=REGIONSIZE+loc.second%REGIONSIZE;
	if(tileLoc.second==REGIONSIZE)
		tileLoc.second=0;
	return tileLoc;
}
WorldTile* GameWorld::lookupTile(std::pair<int,int> loc) const
{
	std::pair<int,int> tileLoc (lookupRegionTilePos(loc));
	return regionCoord.find(lookupRegion(loc))->second->getTile(tileLoc);
}
void GameWorld::addItem(GameItem* lGameItem, std::pair<int,int> loc)
{
		std::map<std::pair<int,int>,std::vector<GameItem*>>::iterator pileIt = gameItemCoord.find(loc);
		//if there is no pile there
		if(pileIt == gameItemCoord.end())
		{
			//make a pile
			std::vector<GameItem*> iTemp;
			gameItemCoord[loc] = iTemp;
		}
		//add the item to the pile
		gameItemCoord[loc].push_back(lGameItem);
}
void GameWorld::removeItem(GameItem* lGameItem, std::pair<int,int> loc)
{
		std::map<std::pair<int,int>,std::vector<GameItem*>>::iterator pileIt = gameItemCoord.find(loc);
		//if an item pile is found in the world
		if(pileIt != gameItemCoord.end())
		{
			std::vector<GameItem*>::iterator itemIt = std::find(pileIt->second.begin(), pileIt->second.end(), lGameItem);
			//if the item is found in the pile
			if(itemIt != pileIt->second.end())
			{
				pileIt->second.erase(itemIt);
				if(pileIt->second.empty())
					gameItemCoord.erase(pileIt);
			}
		}
}
bool GameWorld::moveCreature(Creature* lCreature, std::pair<int,int> loc)
{
	//if it is passable
	if(lookupTile(loc)->isPassable())
		{
			//erase the old marker and place the creature in the new location
			creatureCoord.erase(lCreature->getLocation());
			lCreature->setLocation(loc);
			creatureCoord[loc] = lCreature;
			return true;
		}
	else
		return false;
}
void GameWorld::moveGameItem(GameItem* lGameItem, std::pair<int,int> loc)
{
	//remove the item from the old pile
	std::map<std::pair<int,int>,std::vector<GameItem*>>::iterator pileIt = gameItemCoord.find(lGameItem->getLocation());
	std::vector<GameItem*>::iterator itemIt = std::find(pileIt->second.begin(), pileIt->second.end(), lGameItem);
	//if the item *is* in the pile (it always should be)
	if(itemIt != pileIt->second.end())
	{
		//remove it from the pile
		pileIt->second.erase(itemIt);
		//if the pile is empty remove it from the map
		if(pileIt->second.empty())
		{
			gameItemCoord.erase(pileIt);
		}
	}

	//give the item its new location
	lGameItem->setLocation(loc);
	//place the item in the new pile
	pileIt = gameItemCoord.find(loc);
	//if there is no pile in the new location
	if(pileIt == gameItemCoord.end())
	{
		//make a new pile
		std::vector<GameItem*> iTemp;
		gameItemCoord[loc] = iTemp;
	}
	//add the item to the pile
	gameItemCoord[loc].push_back(lGameItem);
}
void GameWorld::fillArea(std::pair<int,int> point1, std::pair<int,int> point2)
{
	const int x1 = point1.first;
	const int x2 = point2.first;
	const int y1 = point1.second;
	const int y2= point2.second;

		const int width = x2-x1;
		const int height = y2-y1;
		const std::pair<int,int> pointRegion = lookupRegion(point1);
		const int xReg = pointRegion.first;
		const int yReg = pointRegion.second;
		for(int i=0; i<width/REGIONSIZE; i++)
		{
			for(int j = 0; j<height/REGIONSIZE; j++)
			{
				WorldRegion* temp = new WorldRegion();
				std::pair<int,int> loc (xReg+i,yReg+j);
				regionCoord[loc] = temp;
				//Place tiles into regions
				for(int k=0; k<10; k++)
				{
					for(int l =0; l<10; l++)
					{
						temp->setTile(std::pair<int,int>(k,l),new WorldTile(tileTypeDef.getTileType(WorldTileTypeID(0))));
					}
				}
			}
		}
}
void GameWorld::setTile(std::pair<int,int> loc, WorldTile* lTile)
{
	std::pair<int,int> regionLoc = lookupRegion(loc);
	std::pair<int,int> tileLoc = lookupRegionTilePos(loc);
	regionCoord.at(regionLoc)->setTile(tileLoc,lTile);
}
void GameWorld::addCreature(Creature* lCreature, std::pair<int,int> loc)
{
	//add it to the vector
	//creatureList.push_back(lCreature);
	//add it to the coord map
	//TODO: check if there is already a creature there, then act accordingly
	creatureCoord[loc] = lCreature;
}
void GameWorld::removeCreature(Creature* lCreature, std::pair<int,int> loc)
{
	//remove it from the vector
	//remove it from the coord map
	std::map<std::pair<int,int>,Creature*>::iterator creatureIt = creatureCoord.find(loc);
	if(creatureIt != creatureCoord.end() && creatureIt->second == lCreature)
	{
		creatureCoord.erase(creatureIt);
	}
}
std::vector<GameItem*>* GameWorld::getItemPile(std::pair<int,int> loc) const
{
	std::map<std::pair<int,int>,std::vector<GameItem*>>::const_iterator pileIt = gameItemCoord.find(loc);
		//if there is a pile there
		if(pileIt != gameItemCoord.end())
		{
			return const_cast<std::vector<GameItem*>*>(&(pileIt->second));
		}
		else
			return NULL;
}
Creature* GameWorld::getCreature(std::pair<int,int> loc) const
{
	std::map<std::pair<int,int>, Creature*>::const_iterator creatureIt = creatureCoord.find(loc);
	//if there is a creature there
	if(creatureIt != creatureCoord.end())
	{
		return creatureIt->second;
	}
	else
		return NULL;
}
std::vector<Creature*> GameWorld::getCreatureList(void) const
{
	//temporary list we will create
	std::vector<Creature*> creatureList;
	//convert map to vector
	for(std::map<std::pair<int,int>, Creature*>::const_iterator creatureIt = creatureCoord.begin();
		creatureIt != creatureCoord.end(); creatureIt++)
	{
		creatureList.push_back(creatureIt->second);
	}
	//return the local vector
	return creatureList;
}
void GameWorld::setPlayerCreature(Creature* lCreature)
{
	playerCreature = lCreature;
}
Creature* GameWorld::getPlayerCreature(void) const
{
	return playerCreature;
}
void GameWorld::createItem(GameItemTypeID lTypeID, std::pair<int,int> loc)
{
	GameItem* item = new GameItem(itemTypeDef.getTileType(lTypeID), loc);
	addItem(item, loc);
}
void GameWorld::destroyItem(GameItem* lGameItem, std::pair<int,int> loc)
{
	removeItem(lGameItem, loc);
	delete lGameItem;
}
void GameWorld::createCreature(CreatureTypeID lTypeID, std::pair<int,int> loc)
{
	Creature* creature = new Creature(creatureTypeDef.getCreatureType(lTypeID), loc);
	addCreature(creature, loc);
}
void GameWorld::destroyCreature(Creature* lCreature, std::pair<int,int> loc)
{
	removeCreature(lCreature, loc);
	//remove the components
	for(int i = 0; i<lCreature->getNumComponents(); i++)
	{
		delete lCreature->getComponent(EntityComponentID(i));
	}
	delete lCreature;
}