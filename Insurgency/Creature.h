#pragma once
#include "gameentity.h"
#include "CreatureType.h"
#include "CreatureStatEffect.h"
#include <vector>
#include <algorithm>
#include <array>
#include <memory>
#include "InventoryComponent.h"

class Creature :
	public GameEntity
{
public:
	typedef std::unique_ptr<Creature> ptr;

	Creature(const CreatureType& lType);
	virtual ~Creature(void);

	unsigned int getActTurnRem(void);
	void changeActTurnRem(unsigned int amount);

	//get stats
	int getSpeed(void);
	int getStrength(void);
	//base stats
	int getBaseSpeed(void);
	int getBaseStrength(void);

	//change stats
	void addTempStatEffect(CreatureStatEffect lStatEffect);
	void changeSpeedBase(int amount);
	void changeStrengthBase(int amount);

	//update the creature's turn
	void turnUpdate(void);

	InventoryComponent* getInventoryComponent();

private:
	std::array<int, CreatureStat::Count> m_baseStats;
	std::array<int, CreatureStat::Count> m_adjustedStats;

	std::vector<CreatureStatEffect> m_statEffects;

	//how many turns until the action is finished.
	//interruptable actions need a little more framework
	unsigned int m_actTurnRem;

	//don't think I need these
	CreatureTypeID m_type;
	CreatureClassID::E m_class;
};