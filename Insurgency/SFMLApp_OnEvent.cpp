#include "stdafx.h"
#include "SFMLApp.h"

void SFMLApp::OnEvent(sf::Event& Event)
{
	if(m_states.size() == 0)
		return;
	m_states.back()->OnEvent(Event);
	//NOTE - only the top state will accept events, mouse clicks will not carry through, etc.

	while(true)
	{
	SFMLStateMessage* message = m_states.back()->GetStateMessage();
	if(message == NULL)
		break;
	decipherMessage(message);
	delete message;
	}
}

void SFMLApp::OnClose(void)
{
	m_running = false;
}

void SFMLApp::OnResize(int width, int height)
{
}