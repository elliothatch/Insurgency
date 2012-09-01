#pragma once
#include "GameEntity.h"
#include "GameItem.h"
#include "IGameWorld.h"
enum InputMessageID
{
	NOMESSAGE = 0,
	ENTITYDROPITEM = 32,
	OPENPAUSEMENU = 64,
};
class InputMessage
{
public:
	InputMessage(InputMessageID msgID):type(msgID){}
	virtual ~InputMessage(void){}
	InputMessage(const InputMessage& copyName) {type = copyName.getType();}
	InputMessage& operator=(const InputMessage& copyName) {type = copyName.getType();}
	InputMessageID getType(void) const {return type;}
private:
	InputMessageID type;
};

class Msg_None :public InputMessage
{
public:
	Msg_None(void):InputMessage(NOMESSAGE){}
	virtual ~Msg_None(void){}
};

class Msg_EntityDropItem :public InputMessage
{
public:
	Msg_EntityDropItem(GameEntity* lGEntity, GameItem* const lGItem, std::pair<int,int> loc, IGameWorld& lGWorld)
		:InputMessage(ENTITYDROPITEM), gEntity(lGEntity), gItem(lGItem), location(loc), gWorld(lGWorld) {}
	virtual ~Msg_EntityDropItem(void) {}
	GameEntity* getEntity(void) const {return gEntity;}
	GameItem* const getItem(void) const {return gItem;}
	std::pair<int,int> getLocation(void) const {return location;}
	IGameWorld& getWorld(void) const {return gWorld;}
private:
	GameEntity* gEntity;
	GameItem* const gItem;
	std::pair<int,int> location;
	IGameWorld& gWorld;
};

class Msg_OpenPauseMenu :public InputMessage
{
public:
	Msg_OpenPauseMenu(void):InputMessage(OPENPAUSEMENU){}
	virtual ~Msg_OpenPauseMenu(void){}
};