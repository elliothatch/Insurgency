#include "StdAfx.h"
#include "GameStateBase.h"
#include <algorithm>

GameStateBase::GameStateBase(const sf::Window& window)
	:m_window(&window),
	 m_messages(),
	m_transparent(false),
	m_allowSubUpdate(false),
	m_subUpdate(true),
	m_subRender(true)
{
}


GameStateBase::~GameStateBase(void)
{
}

void GameStateBase::drawDisplayList(sf::RenderTarget& target) const
{
	for(std::vector<std::unique_ptr<sf::Drawable>>::const_iterator dispIt(m_displayList.begin());
		dispIt != m_displayList.end(); dispIt++)
	{
		target.draw(**dispIt);
	}
}

void GameStateBase::updateGUIElements()
{
	for(std::vector<SFMLGUIElement*>::iterator guiIt(m_GUIElements.begin()); guiIt != m_GUIElements.end(); guiIt++)
	{
		(*guiIt)->update();
	}
}

void GameStateBase::OnEvent(sf::Event& Event)
{
	SFMLEvent::OnEvent(Event);
}

void GameStateBase::OnClose(void)
{
	m_messages.push_back(new SFMLStateMessage_Close());
}

void GameStateBase::OnResize(int width, int height)
{
	m_messages.push_back(new SFMLStateMessage_Resize(width, height));
}

void GameStateBase::OnMouseButtonPressed(sf::Mouse::Button button, int x, int y)
{
	MouseEvent_Pressed(button, x, y);
}
void GameStateBase::OnMouseButtonReleased(sf::Mouse::Button button, int x, int y)
{
	MouseEvent_Released(button, x, y);
}
void GameStateBase::OnMouseMoved(int x, int y)
{
	MouseEvent_Moved(x, y);
}
SFMLStateMessage* GameStateBase::GetStateMessage(void)
{
	if(m_messages.size() == 0)
		return NULL;
	SFMLStateMessage* retVal(m_messages.back());
	m_messages.pop_back();
	return retVal;
}

void GameStateBase::addStateMessage(SFMLStateMessage* stateMessage)
{
	if(stateMessage)
		m_messages.push_back(stateMessage);
}

void GameStateBase::CleanupDisplayList(void)
{
	m_displayList.clear();
}

void GameStateBase::addDrawable(std::unique_ptr<sf::Drawable> target)
{
	m_displayList.push_back(std::move(target));
}

void GameStateBase::removeDrawable(int index)
{
	m_displayList.erase(m_displayList.begin() + index);
}

void GameStateBase::addGUIElement(std::unique_ptr<SFMLGUIElement> target)
{
	if(!target)
		return;
	m_GUIElements.push_back(target.get());
	m_displayList.push_back(std::move(target));
}

void GameStateBase::removeGUIElement(SFMLGUIElement* target)
{
	std::vector<SFMLGUIElement*>::iterator guiIt(std::find(m_GUIElements.begin(), m_GUIElements.end(), target));
	if(guiIt != m_GUIElements.end())
	{
		m_GUIElements.erase(guiIt);
		
		std::vector<std::unique_ptr<sf::Drawable>>::iterator dispIt(std::find_if(m_displayList.begin(), m_displayList.end(),
			[&](const std::unique_ptr<sf::Drawable>& drawable) {return drawable.get() == target;}));
		if(dispIt != m_displayList.end())
			m_displayList.erase(dispIt);
	}
}

SFMLGUIElement* GameStateBase::getTopGUIElement(int X, int Y)
{
	for(std::vector<SFMLGUIElement*>::reverse_iterator objIt(m_GUIElements.rbegin()); objIt !=  m_GUIElements.rend(); objIt++)
	{
		SFMLGUIElement* guiObj = (*objIt);
		if(pointCollided(guiObj, X, Y))
		{
			return guiObj;
		}
	}
	return nullptr;
}

bool GameStateBase::pointCollided(SFMLGUIElement* target, int X, int Y)
{
	//right now we'll just test this with rectangles
	return target->getGlobalBounds().contains(static_cast<float>(X),static_cast<float>(Y));
}

void GameStateBase::MouseEvent_Pressed(sf::Mouse::Button button, int x, int y)
{
	SFMLGUIElement* guiObj = getTopGUIElement(x, y);
	if(guiObj)
	{
		switch(button)
		{
		case sf::Mouse::Left:
			guiObj->OnMouseLeftPressed();
			break;
		case sf::Mouse::Right:
			guiObj->OnMouseRightPressed();
			break;
		case sf::Mouse::Middle:
			guiObj->OnMouseMiddlePressed();
			break;
		}
	}

}
void GameStateBase::MouseEvent_Released(sf::Mouse::Button button, int x, int y)
{
	SFMLGUIElement* guiObj = getTopGUIElement(x, y);
	if(guiObj)
	{
		switch(button)
		{
		case sf::Mouse::Left:
			guiObj->OnMouseLeftReleased();
			break;
		case sf::Mouse::Right:
			guiObj->OnMouseRightReleased();
			break;
		case sf::Mouse::Middle:
			guiObj->OnMouseMiddleReleased();
			break;
		}
	}
	//tell all gui objs that the mouse has been released
	for(std::vector<SFMLGUIElement*>::iterator objIt(m_GUIElements.begin()); objIt !=  m_GUIElements.end(); objIt++)
	{
		switch(button)
		{
		case sf::Mouse::Left:
			(*objIt)->OnGlobalMouseLeftReleased();
			break;
		case sf::Mouse::Right:
			(*objIt)->OnGlobalMouseRightReleased();
			break;
		case sf::Mouse::Middle:
			(*objIt)->OnGlobalMouseMiddleReleased();
			break;
		}
	}
}
void GameStateBase::MouseEvent_Moved(int x, int y)
{
	SFMLGUIElement* guiObj = getTopGUIElement(x, y);
	if(guiObj)
	{
		guiObj->OnMouseRollover();
	}
}

void GameStateBase::CleanupGUIElements(void)
{
	while(m_GUIElements.size() > 0)
	{
		removeGUIElement(m_GUIElements.front());
	}
	m_GUIElements.clear();
}

const std::vector<std::unique_ptr<sf::Drawable>>& GameStateBase::getDisplayList() const
{
	return m_displayList;
}

const std::vector<SFMLGUIElement*>& GameStateBase::getGUIElements() const
{
	return m_GUIElements;
}

void GameStateBase::Cleanup()
{
	m_GUIElements.clear();
	m_displayList.clear();
}