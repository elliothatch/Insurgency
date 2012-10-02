#include "StdAfx.h"
#include "GameTurnTimer.h"


GameTurnTimer::GameTurnTimer(GameWorld& lGameWorld)
	:m_gameWorld(lGameWorld),
	m_curTurn(0)
{
}


GameTurnTimer::~GameTurnTimer(void)
{
}

void GameTurnTimer::advanceTurn(void)
{
	//get the list of creatures and iterate through, updating each ones' turn
	std::set<Creature::ptr>& creatureList = m_gameWorld.getCreatureSet();
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
	std::set<Creature::ptr>& creatureList = m_gameWorld.getCreatureSet();
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

bool GameTurnTimer::moveCreature(Creature& lCreature, std::pair<int,int> loc)
{
	if(m_gameWorld.moveCreature(lCreature, loc))
	{
		lCreature.changeActTurnRem(lCreature.getSpeed());
		return true;
	}
	return false;
}

bool GameTurnTimer::moveCreatureRight(Creature& lCreature)
{
	std::pair<int,int> loc(lCreature.getLocation());
	loc.first += 1;
	return moveCreature(lCreature,loc);
}
bool GameTurnTimer::moveCreatureUp(Creature& lCreature)
{
	std::pair<int,int> loc(lCreature.getLocation());
	loc.second -= 1;
	return moveCreature(lCreature,loc);
}
bool GameTurnTimer::moveCreatureLeft(Creature& lCreature)
{
	std::pair<int,int> loc(lCreature.getLocation());
	loc.first -= 1;
	return moveCreature(lCreature,loc);
}
bool GameTurnTimer::moveCreatureDown(Creature& lCreature)
{
	std::pair<int,int> loc(lCreature.getLocation());
	loc.second += 1;
	return moveCreature(lCreature,loc);
}

bool GameTurnTimer::creaturePickUpItem(Creature& lCreature, GameItem& lGameItem)
{
	if(m_gameWorld.putEntityInInventory(*lCreature.getInventoryComponent(), lGameItem))
	{
		lCreature.changeActTurnRem(3);
		return true;
	}
	return false;
}

bool GameTurnTimer::creatureDropItem(Creature& lCreature, GameItem& lGameItem)
{
	if(m_gameWorld.removeEntityFromInventory(*lCreature.getInventoryComponent(), lGameItem))
	{
		lCreature.changeActTurnRem(3);
		return true;
	}
	return false;
}

void GameTurnTimer::waitCreature(Creature& lCreature)
{
	lCreature.changeActTurnRem(1);
}