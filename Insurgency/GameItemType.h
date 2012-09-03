#pragma once
#include "GameEntityType.h"
typedef unsigned int GameItemTypeID; //unique type identifier for this item
//typedef unsigned int GameItemClassID; //non-unique type for catagorizing items (i.e. AssaultRifle01 [low quality])
enum GameItemClassID
{
	GameItemClass_NoClass = 0,
	GameItemClass_AssaultRifle01,
	GameItemClassCount
};

class GameItemType : public GameEntityType
{
public:

	GameItemType(void);
	~GameItemType(void);

	//getters
	GameItemTypeID getTypeID(void) const;
	GameItemClassID getClassID(void) const;
	//setters
	void setTypeID(GameItemTypeID lType);
	void setClassID(GameItemClassID lClass);

private:
	GameItemTypeID m_type;
	GameItemClassID m_class;
};