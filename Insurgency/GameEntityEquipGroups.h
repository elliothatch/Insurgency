#pragma once
#include <set>
#include <vector>
struct EntityEquipSlotID
{
	enum E
	{
		HeldRight = 0, //held in your hand
		HeldLeft,
		//armor
		Shirt,
		Pants,
		Shoes,
		Gloves,
		//"on" equip slots
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
		Count
	};
};

class GameEntityEquipGroups
{
public:
	struct EquipGroup
	{
		//ctors
		EquipGroup():m_equipSlots(), m_name(""){}
		EquipGroup(EntityEquipSlotID::E equipSlot):m_equipSlots(),m_name(""){m_equipSlots.insert(equipSlot);}
		EquipGroup(std::set<EntityEquipSlotID::E> equipSlots):m_equipSlots(equipSlots),m_name(""){}
		EquipGroup(const std::string& name):m_equipSlots(), m_name(name){}
		EquipGroup(EntityEquipSlotID::E equipSlot,const std::string& name):m_equipSlots(),m_name(name){m_equipSlots.insert(equipSlot);}
		EquipGroup(std::set<EntityEquipSlotID::E> equipSlots,const std::string& name):m_equipSlots(equipSlots),m_name(name){}

		std::string getName() const;
		std::string setName(const std::string& name) {m_name = name;}
		
		std::set<EntityEquipSlotID::E> m_equipSlots;
	private:
		std::string m_name;
	};

	GameEntityEquipGroups(void);
	~GameEntityEquipGroups(void);

	void addEquipGroup(EquipGroup equipGroup);
	void setEquipGroups(std::vector<EquipGroup> equipGroups);
	const std::vector<EquipGroup>& getEquipGroups() const;

	static std::string getEquipSlotName(EntityEquipSlotID::E id);

private:
	std::vector<EquipGroup> m_equipGroups;
};

