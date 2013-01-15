#include "StdAfx.h"
#include "GameEntityEquipGroups.h"


GameEntityEquipGroups::GameEntityEquipGroups(void)
{
}


GameEntityEquipGroups::~GameEntityEquipGroups(void)
{
}

void GameEntityEquipGroups::addEquipGroup(GameEntityEquipGroups::EquipGroup equipGroup)
{
	m_equipGroups.push_back(equipGroup);
}
void GameEntityEquipGroups::setEquipGroups(std::vector<GameEntityEquipGroups::EquipGroup> equipGroups)
{
	m_equipGroups = equipGroups;
}
std::vector<GameEntityEquipGroups::EquipGroup> GameEntityEquipGroups::getEquipGroups() const
{
	return m_equipGroups;
}