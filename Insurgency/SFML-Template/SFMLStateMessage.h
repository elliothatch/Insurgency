#pragma once
#include <SFML/Window.hpp>

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
	const SFMLStateMessage::Type::E type;
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
	SFMLStateMessage_ChangeState(std::string stateIdentifier)
		:SFMLStateMessage(SFMLStateMessage::Type::ChangeState), m_stateID(stateIdentifier) {}
	virtual ~SFMLStateMessage_ChangeState(void) {}
	std::string m_stateID;
};

class SFMLStateMessage_PushState : public SFMLStateMessage
{
public:
	SFMLStateMessage_PushState(std::string stateIdentifier)
		:SFMLStateMessage(SFMLStateMessage::Type::PushState), m_stateID(stateIdentifier) {}
	virtual ~SFMLStateMessage_PushState(void) {}
	std::string m_stateID;
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