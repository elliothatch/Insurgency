#include "StdAfx.h"
#include "GameWorld.h"


GameWorld::GameWorld(const IWorldTileTypeDef& lWorldTileTypeDef,
					 const ICreatureTypeDef& lCreatureTypeDef,
					 const IGameItemTypeDef& lGameItemTypeDef)
	:m_tileTypeDef(lWorldTileTypeDef),
	 m_creatureTypeDef(lCreatureTypeDef),
	 m_itemTypeDef(lGameItemTypeDef),
	 m_playerCreature(nullptr)
{
	
}
GameWorld::~GameWorld(void)
{
}

//add/remove
void GameWorld::addItemToWorld(GameItem& lGameItem, std::pair<int,int> loc)
{
		std::map<std::pair<int,int>,std::vector<GameItem*>>::iterator pileIt(m_gameItemCoord.find(loc));
		//if there is no pile there
		if(pileIt == m_gameItemCoord.end())
		{
			//make a pile
			std::vector<GameItem*> iTemp;
			m_gameItemCoord[loc] = iTemp;
		}
		//add the item to the pile
		m_gameItemCoord[loc].push_back(&lGameItem);
		lGameItem.setLocation(loc);
}
void GameWorld::removeItemFromWorld(GameItem& lGameItem)
{
		std::map<std::pair<int,int>,std::vector<GameItem*>>::iterator
			pileIt = m_gameItemCoord.find(lGameItem.getLocation());
		//if an item pile is found in the world
		if(pileIt != m_gameItemCoord.end())
		{
			std::vector<GameItem*>::iterator itemIt(std::find_if(pileIt->second.begin(), pileIt->second.end(),
				[&](GameItem* item){return item == &lGameItem;}));
			//if the item is found in the pile
			if(itemIt != pileIt->second.end())
			{
				pileIt->second.erase(itemIt);
				if(pileIt->second.empty())
					m_gameItemCoord.erase(pileIt);
			}
		}
}
void GameWorld::addCreatureToWorld(Creature& lCreature, std::pair<int,int> loc)
{
	//add it to the vector
	//creatureList.push_back(lCreature);
	//add it to the coord map
	//TODO: check if there is already a creature there, then act accordingly
	m_creatureCoord[loc] = &lCreature;
	lCreature.setLocation(loc);
}
void GameWorld::removeCreatureFromWorld(Creature& lCreature)
{
	//remove it from the coord map
	std::map<std::pair<int,int>,Creature*>::iterator creatureIt(m_creatureCoord.find(lCreature.getLocation()));
	if(creatureIt != m_creatureCoord.end() && creatureIt->second == &lCreature)
	{
		m_creatureCoord.erase(creatureIt);
	}
}
//create/destroy
GameItem& GameWorld::createItem(GameItemTypeID lTypeID)
{   
	return **m_gameItems.insert(new GameItem(m_itemTypeDef.getTileType(lTypeID))).first;
}
void GameWorld::destroyItem(GameItem& lGameItem)
{
	if(!lGameItem.getIsEnclosed())
	{
	removeItemFromWorld(lGameItem);
	}
	std::set<GameItem::ptr>::iterator itemIt(std::find_if(m_gameItems.begin(), m_gameItems.end(), 
		[&](const GameItem::ptr& item) {return item.get() == &lGameItem;}));
	if(itemIt != m_gameItems.end())
		m_gameItems.erase(itemIt);
}
Creature& GameWorld::createCreature(CreatureTypeID lTypeID)
{
	return **m_creatures.insert(new Creature(m_creatureTypeDef.getCreatureType(lTypeID))).first;
}
void GameWorld::destroyCreature(Creature& lCreature)
{
	if(!lCreature.getIsEnclosed())
	{
		removeCreatureFromWorld(lCreature);
	}
	std::set<Creature::ptr>::iterator creatureIt(std::find_if(m_creatures.begin(), m_creatures.end(), 
		[&](const Creature::ptr& creature) {return creature.get() == &lCreature;}));
	if(creatureIt != m_creatures.end())
		m_creatures.erase(creatureIt);
}
//get entities
std::vector<GameItem*>* GameWorld::getItemPile(std::pair<int,int> loc) const
{
	std::map<std::pair<int,int>,std::vector<GameItem*>>::const_iterator pileIt = m_gameItemCoord.find(loc);
		//if there is a pile there
		if(pileIt != m_gameItemCoord.end())
		{
			return const_cast<std::vector<GameItem*>*>(&pileIt->second);
		}
		else
			return nullptr;
}
Creature* GameWorld::getCreature(std::pair<int,int> loc) const
{
	std::map<std::pair<int,int>, Creature*>::const_iterator creatureIt = m_creatureCoord.find(loc);
	//if there is a creature there
	if(creatureIt != m_creatureCoord.end())
	{
		return creatureIt->second;
	}
	else
		return nullptr;
}
//creatures
std::set<Creature::ptr>& GameWorld::getCreatureSet(void) const
{
	return const_cast<std::set<Creature::ptr>&>(m_creatures);
}
Creature* GameWorld::getPlayerCreature(void) const
{
	return m_playerCreature;
}
void GameWorld::setPlayerCreature(Creature& lCreature)
{
	m_playerCreature = &lCreature;
}
//events
void GameWorld::moveGameItem(GameItem& lGameItem, std::pair<int,int> loc)
{
	removeItemFromWorld(lGameItem);
	addItemToWorld(lGameItem, loc);
}
bool GameWorld::moveCreature(Creature& lCreature, std::pair<int,int> loc)
{
	//if it is passable
	if(lookupTile(loc).isPassable())
		{
			removeCreatureFromWorld(lCreature);
			addCreatureToWorld(lCreature, loc);
			return true;
		}
	else
		return false;
}
//lookup world-space
WorldTile& GameWorld::lookupTile(std::pair<int,int> loc) const
{
	std::pair<int,int> tileLoc (lookupRegionTilePos(loc));
	return m_regionCoord.find(lookupRegion(loc))->second->getTile(tileLoc);
}
std::pair<int,int> GameWorld::lookupRegion(std::pair<int,int> loc) const 
{
	return std::pair<int,int>  (int(floor(float(loc.first)/float(WorldRegion::kRegionSize))),
								int(floor(float(loc.second)/float(WorldRegion::kRegionSize))));
}
std::pair<int,int> GameWorld::lookupRegionTilePos(std::pair<int,int> loc) const
{
	std::pair<int,int> tileLoc;
	//xcoord
	if(loc.first>=0)
		tileLoc.first=loc.first%WorldRegion::kRegionSize;
	else
		tileLoc.first=WorldRegion::kRegionSize+loc.first%WorldRegion::kRegionSize;
	if(tileLoc.first==WorldRegion::kRegionSize)
		tileLoc.first=0;
	//y coord
	if(loc.second>=0)
		tileLoc.second=loc.second%WorldRegion::kRegionSize;
	else
		tileLoc.second=WorldRegion::kRegionSize+loc.second%WorldRegion::kRegionSize;
	if(tileLoc.second==WorldRegion::kRegionSize)
		tileLoc.second=0;
	return tileLoc;
}
//set world-space
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
		for(int i=0; i<width/WorldRegion::kRegionSize; i++)
		{
			for(int j = 0; j<height/WorldRegion::kRegionSize; j++)
			{
				WorldRegion::ptr temp(new WorldRegion());
				std::pair<int,int> loc (xReg+i,yReg+j);
				//Place tiles into regions
				for(int k=0; k<10; k++)
				{
					for(int l =0; l<10; l++)
					{
						WorldTile::ptr tile(new WorldTile(m_tileTypeDef.getTileType(WorldTileTypeID(0))));
						temp->setTile(std::pair<int,int>(k,l),std::move(tile));
					}
				}
				m_regionCoord[loc] = std::move(temp);
			}
		}
}
void GameWorld::setTile(std::pair<int,int> loc, WorldTile::ptr lTile)
{
	std::pair<int,int> regionLoc = lookupRegion(loc);
	std::pair<int,int> tileLoc = lookupRegionTilePos(loc);
	m_regionCoord.at(regionLoc)->setTile(tileLoc,std::move(lTile));
}
