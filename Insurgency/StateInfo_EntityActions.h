#include "SFML-Template/SFMLStateInfo.h"

class GameEntity;
class GameTurnTimer;
class SFMLStateInfo_EntityActions :public SFMLStateInfo
{
public:
	SFMLStateInfo_EntityActions(int x, int y, GameEntity* entity)
		:m_entity(entity) {}
	virtual ~SFMLStateInfo_EntityActions() {}
	GameEntity* m_entity;
};
