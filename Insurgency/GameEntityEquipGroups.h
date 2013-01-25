#pragma once
#include <set>
#include <vector>
struct EntityEquipSlotID
{
	enum E
	{
		HeldRight = 0, //held in your hand
		HeldLeft,
		//armor slots
		HandRight,     //gloves, etc.
		HandLeft,
		ForearmRight,
		ForearmLeft,
		ShoulderRight,
		ShoulderLeft,
		Neck,
		Head,
		Eyes,	//goggles/blindfold
		Chest,
		Abdomen,
		Groin,
		ThighRight,
		ThighLeft,
		ShinRight,
		ShinLeft,
		FootRight,
		FootLeft,
		//on top of armor e.g. holster
		OnHandRight,
		OnHandLeft,
		OnForearmRight,
		OnForearmLeft,
		OnShoulderRight,
		OnShoulderLeft,
		OnNeck,
		OnHead,
		OnChest,
		OnAbdomen,
		OnGroin,
		OnThighRight,
		OnThighLeft,
		OnShinRight,
		OnShinLeft,
		OnFootRight,
		OnFootLeft,
		Count
	};
};

class GameEntityEquipGroups
{
public:
	struct EquipGroup
	{
		EquipGroup():m_equipSlots(){}
		EquipGroup(EntityEquipSlotID::E equipSlot):m_equipSlots(){m_equipSlots.insert(equipSlot);}
		EquipGroup(std::set<EntityEquipSlotID::E> equipSlots):m_equipSlots(equipSlots){}
		std::set<EntityEquipSlotID::E> m_equipSlots;
	};

	GameEntityEquipGroups(void);
	~GameEntityEquipGroups(void);

	void addEquipGroup(EquipGroup equipGroup);
	void setEquipGroups(std::vector<EquipGroup> equipGroups);
	const std::vector<EquipGroup>& getEquipGroups() const;

private:
	std::vector<EquipGroup> m_equipGroups;
};

