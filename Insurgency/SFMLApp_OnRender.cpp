#include "stdafx.h"
#include "SFMLApp.h"

void SFMLApp::OnRender(void)
{	if(m_states.size() == 0)
	{
		printf("!!! No states to render!\n");
		return;
	}
	std::vector<GameStateBase*> renderList;
	if(m_states.size() > 1 && m_states.back()->m_transparent)
	{
		for(std::vector<GameStateBase*>::reverse_iterator stateIt(m_states.rbegin()+1); stateIt != m_states.rend(); stateIt++)
		{
			if((*stateIt)->m_subRender)
				renderList.push_back(*stateIt);
			if(!(*stateIt)->m_transparent)
				break;
		}
	}
	//front state always renders on top
	renderList.push_back(m_states.back());

	m_mainWindow.clear();
	for(std::vector<GameStateBase*>::iterator stateIt(renderList.begin()); stateIt != renderList.end(); stateIt++)
	{
		(*stateIt)->OnRender(m_mainWindow);
	}
	m_mainWindow.display();
}