#include "StdAfx.h"
#include "SFMLGUIElement.h"


SFMLGUIElement::SFMLGUIElement(void)
	:sf::Drawable(), sf::Transformable(),
	 m_leftPressed(false), m_rightPressed(false), m_middlePressed(false),
	 m_mouseX(0), m_mouseY(0),
	 m_MouseLeftPressedfunc(nullptr), m_MouseLeftReleasedfunc(nullptr),
	 m_MouseRightPressedfunc(nullptr), m_MouseRightReleasedfunc(nullptr),
	 m_MouseMiddlePressedfunc(nullptr), m_MouseMiddleReleasedfunc(nullptr),
	 m_MouseLeftClickedfunc(nullptr), m_MouseRightClickedfunc(nullptr), m_MouseMiddleClickedfunc(nullptr)
{
}

SFMLGUIElement::~SFMLGUIElement(void)
{
}

void SFMLGUIElement::OnMouseLeftPressed(int x, int y)
{
	m_leftPressed = true;
	m_mouseX = x;
	m_mouseY = y;
	if(m_MouseLeftPressedfunc != nullptr)
		(*m_MouseLeftPressedfunc)();

}

void SFMLGUIElement::OnMouseLeftReleased(int x, int y)
{
	m_mouseX = x;
	m_mouseY = y;
	if(m_leftPressed)
	{	
		if(m_MouseLeftClickedfunc != nullptr)
			(*m_MouseLeftClickedfunc)();
	}
	else if(m_MouseLeftReleasedfunc != nullptr)
		(*m_MouseLeftReleasedfunc)();
}

void SFMLGUIElement::OnMouseRightPressed(int x, int y)
{
	m_rightPressed = true;
	m_mouseX = x;
	m_mouseY = y;
	if(m_MouseRightPressedfunc != nullptr)
		(*m_MouseRightPressedfunc)();
}

void SFMLGUIElement::OnMouseRightReleased(int x, int y)
{
	m_mouseX = x;
	m_mouseY = y;
	if(m_rightPressed)
	{	
		if(m_MouseRightClickedfunc != nullptr)
			(*m_MouseRightClickedfunc)();
	}
	else if(m_MouseRightReleasedfunc != nullptr)
		(*m_MouseRightReleasedfunc)();
}

void SFMLGUIElement::OnMouseMiddlePressed(int x, int y)
{
	m_middlePressed = true;
	m_mouseX = x;
	m_mouseY = y;
	if(m_MouseMiddlePressedfunc != nullptr)
		(*m_MouseMiddlePressedfunc)();
}

void SFMLGUIElement::OnMouseMiddleReleased(int x, int y)
{
	m_mouseX = x;
	m_mouseY = y;
	if(m_middlePressed)
	{	
		if(m_MouseMiddleClickedfunc != nullptr)
			(*m_MouseMiddleClickedfunc)();
	}
	else if(m_MouseMiddleReleasedfunc != nullptr)
		(*m_MouseMiddleReleasedfunc)();
}

void SFMLGUIElement::OnMouseRollover(int x, int y)
{
	m_mouseX = x;
	m_mouseY = y;
	if(m_MouseRolloverfunc)
	{
		(*m_MouseRolloverfunc)();
	}
}

void SFMLGUIElement::OnGlobalMouseLeftReleased(int x, int y)
{
	m_leftPressed = false;
	m_mouseX = x;
	m_mouseY = y;
}

void SFMLGUIElement::OnGlobalMouseRightReleased(int x, int y)
{
	m_rightPressed = false;
	m_mouseX = x;
	m_mouseY = y;
}

void SFMLGUIElement::OnGlobalMouseMiddleReleased(int x, int y)
{
	m_middlePressed = false;
	m_mouseX = x;
	m_mouseY = y;
}
