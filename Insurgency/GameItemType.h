#pragma once
#include "GameEntityType.h"
typedef unsigned int GameItemTypeID; //unique type identifier for this item
//typedef unsigned int GameItemClassID; //non-unique type for catagorizing items (i.e. AssaultRifle01 [low quality])
struct GameItemClassID
{
	enum E
	{
		None = 0,
		AssaultRifle01,
		Count
	};
};

class GameItemType : public GameEntityType
{
public:

	GameItemType(void);
	~GameItemType(void);

	//getters
	GameItemTypeID getTypeID(void) const;
	GameItemClassID::E getClassID(void) const;
	//setters
	void setTypeID(GameItemTypeID lType);
	void setClassID(GameItemClassID::E lClass);

private:
	GameItemTypeID m_type;
	GameItemClassID::E m_class;
};