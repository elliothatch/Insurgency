#include "StdAfx.h"
#include "SFMLGUIElement.h"


SFMLGUIElement::SFMLGUIElement(void)
	:sf::Drawable(), sf::Transformable(),
	 m_leftPressed(false), m_rightPressed(false), m_middlePressed(false),
	 m_MouseLeftPressedfunc(nullptr), m_MouseLeftReleasedfunc(nullptr),
	 m_MouseRightPressedfunc(nullptr), m_MouseRightReleasedfunc(nullptr),
	 m_MouseMiddlePressedfunc(nullptr), m_MouseMiddleReleasedfunc(nullptr),
	 m_MouseLeftClickedfunc(nullptr), m_MouseRightClickedfunc(nullptr), m_MouseMiddleClickedfunc(nullptr)
{
}

SFMLGUIElement::~SFMLGUIElement(void)
{
}

void SFMLGUIElement::OnMouseLeftPressed(void)
{
	m_leftPressed = true;
	if(m_MouseLeftPressedfunc != nullptr)
		(*m_MouseLeftPressedfunc)();

}

void SFMLGUIElement::OnMouseLeftReleased(void)
{
	if(m_leftPressed)
	{	
		if(m_MouseLeftClickedfunc != nullptr)
			(*m_MouseLeftClickedfunc)();
	}
	else if(m_MouseLeftReleasedfunc != nullptr)
		(*m_MouseLeftReleasedfunc)();
}

void SFMLGUIElement::OnMouseRightPressed(void)
{
	m_rightPressed = true;
	if(m_MouseRightPressedfunc != nullptr)
		(*m_MouseRightPressedfunc)();
}

void SFMLGUIElement::OnMouseRightReleased(void)
{
	if(m_rightPressed)
	{	
		if(m_MouseRightClickedfunc != nullptr)
			(*m_MouseRightClickedfunc)();
	}
	else if(m_MouseRightReleasedfunc != nullptr)
		(*m_MouseRightReleasedfunc)();
}

void SFMLGUIElement::OnMouseMiddlePressed(void)
{
	m_middlePressed = true;
	if(m_MouseMiddlePressedfunc != nullptr)
		(*m_MouseMiddlePressedfunc)();
}

void SFMLGUIElement::OnMouseMiddleReleased(void)
{
	if(m_middlePressed)
	{	
		if(m_MouseMiddleClickedfunc != nullptr)
			(*m_MouseMiddleClickedfunc)();
	}
	else if(m_MouseMiddleReleasedfunc != nullptr)
		(*m_MouseMiddleReleasedfunc)();
}

void SFMLGUIElement::OnGlobalMouseLeftReleased(void)
{
	m_leftPressed = false;
}

void SFMLGUIElement::OnGlobalMouseRightReleased(void)
{
	m_rightPressed = false;
}

void SFMLGUIElement::OnGlobalMouseMiddleReleased(void)
{
	m_middlePressed = false;
}
