#pragma once
#include "GameEntityType.h"
typedef unsigned int GameItemTypeID; //unique type identifier for this item
//typedef unsigned int GameItemClassID; //non-unique type for catagorizing items (i.e. AssaultRifle01 [low quality])
enum GameItemClassID
{
	NOITEMCLASS = 0,
	assaultRifle01,
};

class GameItemType : public GameEntityType
{
public:

	GameItemType(void)
		:GameEntityType(),
		 m_type(NULL),
		 m_class(NOITEMCLASS)
	{
	}

	~GameItemType(void)
	{
	}

	//getters
	GameItemTypeID getTypeID(void) const {return m_type;}
	GameItemClassID getClassID(void) const {return m_class;}
	//setters
	void setTypeID(GameItemTypeID lType) {m_type = lType;}
	void setClassID(GameItemClassID lClass) {m_class = lClass;}

private:
	GameItemTypeID m_type;
	GameItemClassID m_class;
};