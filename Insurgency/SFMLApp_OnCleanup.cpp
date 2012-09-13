#include "stdafx.h"
#include "SFMLApp.h"

void SFMLApp::OnCleanup(void)
{
	for(std::vector<GameStateBase*>::iterator stateIt(m_states.begin()); stateIt != m_states.end(); stateIt++)
	{
		(*stateIt)->OnCleanup();
	}
	m_states.clear();
	m_registeredGameStates.clear();
	ImageManager::cleanup();
	SpriteManager::cleanup();
	TextureManager::cleanup();
	SoundManager::cleanup();
	FontManager::cleanup();
}