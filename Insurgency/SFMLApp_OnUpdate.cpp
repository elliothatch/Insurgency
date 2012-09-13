#include "stdafx.h"
#include "SFMLApp.h"

void SFMLApp::OnUpdate(void)
{
	if(m_states.size() == 0)
	{
		printf("!!! No states to update!\n");
		return;
	}
	std::vector<GameStateBase*> updateList;
	//front always updates
	updateList.push_back(m_states.back());
	if(m_states.size() > 1 && m_states.back()->m_allowSubUpdate)
	{
		for(std::vector<GameStateBase*>::reverse_iterator stateIt(m_states.rbegin()+1); stateIt != m_states.rend(); stateIt++)
		{
			if((*stateIt)->m_subUpdate)
				updateList.push_back(*stateIt);
			if(!(*stateIt)->m_allowSubUpdate)
				break;
		}
	}
	for(std::vector<GameStateBase*>::iterator stateIt(updateList.begin()); stateIt != updateList.end(); stateIt++)
	{
			(*stateIt)->OnUpdate();
	}
}
