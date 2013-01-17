#include "StdAfx.h"
#include "GameTurnTimer.h"


GameTurnTimer::GameTurnTimer(GameWorld& gameWorld)
	:m_gameWorld(&gameWorld),
	m_curTurn(0)
{
}


GameTurnTimer::~GameTurnTimer(void)
{
}

void GameTurnTimer::advanceTurn(void)
{
	//get the list of creatures and iterate through, updating each ones' turn
	std::set<Creature::ptr>& creatureList = m_gameWorld->getCreatureSet();
	for(std::set<Creature::ptr>::iterator creatureIt = creatureList.begin();
		creatureIt != creatureList.end(); creatureIt++)
	{
		Creature& curCreature = **creatureIt;
		/*
		if(curCreature->getActTurnRem() == 0)
		{
			//if the creature can act and it is the player, add the character input source
			//let's rethink this...
			//the function needs to alert the game that it should take IO
			if(curCreature == gameWorld.getPlayerCreature())
			{
				//add the source based on the input type
				/*
				extern InputType g_InputType;
				if(g_InputType == CURSES)
				{
					
				}
				*/
			/*
			}
			//if it is an NPC, process its turn
			else
				processNPCTurn();
		}
	*/
		curCreature.turnUpdate();
	}
	m_curTurn++;
}

Creature& GameTurnTimer::nextCreatureTurn(void)
{
	if(m_actingCreatures.size() == 0) //may be able to remove
	{
		m_actingCreatures = getCreaturesCanMove();
	}

	std::vector<Creature*>::iterator creatureIt(m_actingCreatures.end() - 1);
	if((*creatureIt)->getActTurnRem() == 0)
		return **creatureIt;
	else //the last creature in the list cannot move anymore
	{
		m_actingCreatures.pop_back();
		while(m_actingCreatures.size() == 0) //if that was the last creature
		{
			advanceTurn();
			m_actingCreatures = getCreaturesCanMove();
		}
		creatureIt = m_actingCreatures.end() - 1;
		return **creatureIt;
	}
}

std::vector<Creature*> GameTurnTimer::getCreaturesCanMove(void) const
{
	//the vector we return
	std::vector<Creature*> movableCreatures;
	//temp set
	std::set<Creature::ptr>& creatureList = m_gameWorld->getCreatureSet();
	for(std::set<Creature::ptr>::iterator creatureIt = creatureList.begin();
		creatureIt != creatureList.end(); creatureIt++)
	{
		Creature& curCreature = **creatureIt;
		//if the creature can move, add it to the list
		if(curCreature.getActTurnRem() == 0)
		{
			movableCreatures.push_back(&curCreature);
		}
	}
	//sort the list by speed in decending order (front = 0, back = 10, etc), that way we can pop the back after a creature moves
	std::sort(movableCreatures.begin(), movableCreatures.end(), 
		[](Creature* a, Creature* b) {return (a->getSpeed() > b->getSpeed());});
	return movableCreatures;
}

unsigned int GameTurnTimer::getTurnCount() const
{
	return m_curTurn;
}

bool GameTurnTimer::moveCreature(Creature& creature, std::pair<int,int> loc)
{
	if(m_gameWorld->moveCreature(creature, loc))
	{
		creature.changeActTurnRem(creature.getSpeed());
		return true;
	}
	return false;
}

bool GameTurnTimer::moveCreatureRight(Creature& creature)
{
	std::pair<int,int> loc(creature.getLocation());
	loc.first += 1;
	return moveCreature(creature,loc);
}
bool GameTurnTimer::moveCreatureUp(Creature& creature)
{
	std::pair<int,int> loc(creature.getLocation());
	loc.second -= 1;
	return moveCreature(creature,loc);
}
bool GameTurnTimer::moveCreatureLeft(Creature& creature)
{
	std::pair<int,int> loc(creature.getLocation());
	loc.first -= 1;
	return moveCreature(creature,loc);
}
bool GameTurnTimer::moveCreatureDown(Creature& creature)
{
	std::pair<int,int> loc(creature.getLocation());
	loc.second += 1;
	return moveCreature(creature,loc);
}

bool GameTurnTimer::creaturePickUpItem(Creature& creature, GameItem& gameItem)
{
	if(m_gameWorld->putEntityInInventory(*creature.getInventoryComponent(), gameItem))
	{
		creature.changeActTurnRem(3);
		return true;
	}
	return false;
}

bool GameTurnTimer::creatureDropItem(Creature& creature, GameItem& gameItem)
{
	if(creature.getEquipSlotsComponent()->isEntityEquipped(gameItem))
	{
		if(m_gameWorld->entityUnequipEntity(creature, gameItem) && 
			m_gameWorld->removeEntityFromInventory(*creature.getInventoryComponent(), gameItem))
		{
			creature.changeActTurnRem(3);
			return true;
		}
	}
	if(m_gameWorld->removeEntityFromInventory(*creature.getInventoryComponent(), gameItem))
	{
		creature.changeActTurnRem(3);
		return true;
	}
	return false;
}

void GameTurnTimer::waitCreature(Creature& creature)
{
	creature.changeActTurnRem(1);
}

bool GameTurnTimer::creatureEquipItem(Creature& creature, GameItem& gameItem, const GameEntityEquipGroups::EquipGroup& equipGroup)
{
	if(m_gameWorld->entityEquipEntity(creature, gameItem, equipGroup))
	{
		creature.changeActTurnRem(3);
		return true;
	}
	return false;
}

bool GameTurnTimer::creatureUnequipItem(Creature& creature, GameItem& gameItem)
{
	if(m_gameWorld->entityUnequipEntity(creature, gameItem))
	{
		creature.changeActTurnRem(3);
		return true;
	}
	return false;
}