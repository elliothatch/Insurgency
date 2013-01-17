#pragma once
#include <SFML/Window.hpp>
#include "SFMLStateInfo.h"

class SFMLStateMessage
{
public:
	struct Type
	{
		enum E
		{
			None = 0,
			Close,
			Resize,
			ChangeState,
			PushState,
			PopState,
			RemoveState,
			Count
		};
	};
protected:
	//SFMLStateMessage():m_type(None) {}
	SFMLStateMessage(SFMLStateMessage::Type::E type):type(type) {}
public:
	virtual ~SFMLStateMessage(void) {}
	const SFMLStateMessage::Type::E getType(void) {return type;}

private:
	SFMLStateMessage::Type::E type; //const
};

class SFMLStateMessage_Close : public SFMLStateMessage
{
public:
	SFMLStateMessage_Close(void)
		:SFMLStateMessage(SFMLStateMessage::Type::Close) {}
	virtual ~SFMLStateMessage_Close(void) {}
};

class SFMLStateMessage_Resize : public SFMLStateMessage
{
public:
	SFMLStateMessage_Resize(int width, int height)
		:SFMLStateMessage(SFMLStateMessage::Type::Resize), m_width(width), m_height(height) {}
	virtual ~SFMLStateMessage_Resize(void) {}
	int m_width;
	int m_height;
};

class SFMLStateMessage_ChangeState : public SFMLStateMessage
{
public:
	SFMLStateMessage_ChangeState(std::string stateIdentifier, SFMLStateInfo::ptr lStateInfo)
		:SFMLStateMessage(SFMLStateMessage::Type::ChangeState), m_stateID(stateIdentifier), m_stateInfo(std::move(lStateInfo)) {}
	virtual ~SFMLStateMessage_ChangeState(void) {}
	std::string m_stateID;
	SFMLStateInfo::ptr m_stateInfo;
};

class SFMLStateMessage_PushState : public SFMLStateMessage
{
public:
	SFMLStateMessage_PushState(std::string stateIdentifier, SFMLStateInfo::ptr lStateInfo)
		:SFMLStateMessage(SFMLStateMessage::Type::PushState), m_stateID(stateIdentifier), m_stateInfo(std::move(lStateInfo)) {}
	virtual ~SFMLStateMessage_PushState(void) {}
	std::string m_stateID;
	SFMLStateInfo::ptr m_stateInfo;
};

class SFMLStateMessage_PopState : public SFMLStateMessage
{
public:
	SFMLStateMessage_PopState(void)
		:SFMLStateMessage(SFMLStateMessage::Type::PopState){}
	virtual ~SFMLStateMessage_PopState(void) {}
};

class SFMLStateMessage_RemoveState : public SFMLStateMessage
{
public:
	SFMLStateMessage_RemoveState(std::string stateIdentifier)
		:SFMLStateMessage(SFMLStateMessage::Type::RemoveState), m_stateID(stateIdentifier) {}
	virtual ~SFMLStateMessage_RemoveState(void) {}
	std::string m_stateID;
};