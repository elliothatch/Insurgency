#include "StdAfx.h"
#include "SFMLGUIElement.h"


SFMLGUIElement::SFMLGUIElement(const sf::Window& window)
	:sf::Drawable(), sf::Transformable(),
	 m_leftPressed(false), m_rightPressed(false), m_middlePressed(false),
	 m_window(window),
	 m_MouseLeftPressedfunc(), m_MouseLeftReleasedfunc(),
	 m_MouseRightPressedfunc(), m_MouseRightReleasedfunc(),
	 m_MouseMiddlePressedfunc(), m_MouseMiddleReleasedfunc(),
	 m_MouseLeftClickedfunc(), m_MouseRightClickedfunc(), m_MouseMiddleClickedfunc()
{
}

SFMLGUIElement::~SFMLGUIElement(void)
{
}

void SFMLGUIElement::update()
{
	//empty
}

sf::Vector2f SFMLGUIElement::getLocalPoint(float x, float y) const
{
	sf::FloatRect bounds(getGlobalBounds());
	if(!bounds.contains(sf::Vector2f(x,y)))
	{
		throw std::out_of_range("Point outside GUIElement");
	}
	return sf::Vector2f(x - getPosition().x, y - getPosition().y);
}

sf::Vector2f SFMLGUIElement::getLocalPoint(const sf::Vector2f& point) const
{
	sf::FloatRect bounds(getGlobalBounds());
	if(!bounds.contains(point))
	{
		throw std::out_of_range("Point outside GUIElement");
	}
	return sf::Vector2f(point.x - getPosition().x, point.y - getPosition().y);
}
sf::Vector2i SFMLGUIElement::getLocalPoint(int x, int y) const
{
	sf::FloatRect bounds(getGlobalBounds());
	if(!bounds.contains(sf::Vector2f(static_cast<float>(x),static_cast<float>(y))))
	{
		throw std::out_of_range("Point outside GUIElement");
	}
	return sf::Vector2i(x - static_cast<int>(getPosition().x), y - static_cast<int>(getPosition().y));
}
sf::Vector2i SFMLGUIElement::getLocalPoint(const sf::Vector2i& point) const
{
	sf::FloatRect bounds(getGlobalBounds());
	if(!bounds.contains(sf::Vector2f(point)))
	{
		throw std::out_of_range("Point outside GUIElement");
	}
	return sf::Vector2i(point.x - static_cast<int>(getPosition().x), point.y - static_cast<int>(getPosition().y));
}

void SFMLGUIElement::OnMouseLeftPressed()
{
	m_leftPressed = true;
	for(std::vector<std::shared_ptr<TFunctorBase>>::iterator funcIt(m_MouseLeftPressedfunc.begin()); 
		funcIt != m_MouseLeftPressedfunc.end(); funcIt++)
	{
		(**funcIt)();
	}

}

void SFMLGUIElement::OnMouseLeftReleased()
{
	if(m_leftPressed)
	{	
		for(std::vector<std::shared_ptr<TFunctorBase>>::iterator funcIt(m_MouseLeftClickedfunc.begin()); 
			funcIt != m_MouseLeftClickedfunc.end(); funcIt++)
		{
			(**funcIt)();
		}
	}
	else 
	{
		for(std::vector<std::shared_ptr<TFunctorBase>>::iterator funcIt(m_MouseLeftReleasedfunc.begin()); 
		funcIt != m_MouseLeftReleasedfunc.end(); funcIt++)
		{
			(**funcIt)();
		}
	}
}

void SFMLGUIElement::OnMouseRightPressed()
{
	m_rightPressed = true;
	for(std::vector<std::shared_ptr<TFunctorBase>>::iterator funcIt(m_MouseRightPressedfunc.begin()); 
		funcIt != m_MouseRightPressedfunc.end(); funcIt++)
	{
		(**funcIt)();
	}
}

void SFMLGUIElement::OnMouseRightReleased()
{
	if(m_rightPressed)
	{	
		for(std::vector<std::shared_ptr<TFunctorBase>>::iterator funcIt(m_MouseRightClickedfunc.begin()); 
			funcIt != m_MouseRightClickedfunc.end(); funcIt++)
		{
			(**funcIt)();
		}
	}
	else 
	{
		for(std::vector<std::shared_ptr<TFunctorBase>>::iterator funcIt(m_MouseRightReleasedfunc.begin()); 
			funcIt != m_MouseRightReleasedfunc.end(); funcIt++)
		{
			(**funcIt)();
		}
	}
}

void SFMLGUIElement::OnMouseMiddlePressed()
{
	m_middlePressed = true;
	for(std::vector<std::shared_ptr<TFunctorBase>>::iterator funcIt(m_MouseMiddlePressedfunc.begin()); 
		funcIt != m_MouseMiddlePressedfunc.end(); funcIt++)
	{
		(**funcIt)();
	}
}

void SFMLGUIElement::OnMouseMiddleReleased()
{
	if(m_middlePressed)
	{	
		for(std::vector<std::shared_ptr<TFunctorBase>>::iterator funcIt(m_MouseMiddleClickedfunc.begin()); 
			funcIt != m_MouseMiddleClickedfunc.end(); funcIt++)
		{
			(**funcIt)();
		}
	}
	else 
	{
		for(std::vector<std::shared_ptr<TFunctorBase>>::iterator funcIt(m_MouseMiddleReleasedfunc.begin()); 
			funcIt != m_MouseMiddleReleasedfunc.end(); funcIt++)
		{
			(**funcIt)();
		}
	}
}

void SFMLGUIElement::OnMouseRollover()
{
	for(std::vector<std::shared_ptr<TFunctorBase>>::iterator funcIt(m_MouseRolloverfunc.begin()); 
		funcIt != m_MouseRolloverfunc.end(); funcIt++)
	{
		(**funcIt)();
	}
}

void SFMLGUIElement::OnGlobalMouseLeftReleased()
{
	m_leftPressed = false;
}

void SFMLGUIElement::OnGlobalMouseRightReleased()
{
	m_rightPressed = false;
}

void SFMLGUIElement::OnGlobalMouseMiddleReleased()
{
	m_middlePressed = false;
}

void SFMLGUIElement::addMouseLeftPressedFunction(std::shared_ptr<TFunctorBase> func)
{
	m_MouseLeftPressedfunc.push_back(func);
}
void SFMLGUIElement::addMouseLeftReleasedFunction(std::shared_ptr<TFunctorBase> func)
{
	m_MouseLeftReleasedfunc.push_back(func);
}
void SFMLGUIElement::addMouseRightPressedFunction(std::shared_ptr<TFunctorBase> func)
{
	m_MouseRightPressedfunc.push_back(func);
}
void SFMLGUIElement::addMouseRightReleasedFunction(std::shared_ptr<TFunctorBase> func)
{
	m_MouseRightReleasedfunc.push_back(func);
}
void SFMLGUIElement::addMouseMiddlePressedFunction(std::shared_ptr<TFunctorBase> func)
{
	m_MouseMiddlePressedfunc.push_back(func);
}
void SFMLGUIElement::addMouseMiddleReleasedFunction(std::shared_ptr<TFunctorBase> func)
{
	m_MouseMiddleReleasedfunc.push_back(func);
}
void SFMLGUIElement::addMouseLeftClickedFunction(std::shared_ptr<TFunctorBase> func)
{
	m_MouseLeftClickedfunc.push_back(func);
}
void SFMLGUIElement::addMouseRightClickedFunction(std::shared_ptr<TFunctorBase> func)
{
	m_MouseRightClickedfunc.push_back(func);
}
void SFMLGUIElement::addMouseMiddleClickedFunction(std::shared_ptr<TFunctorBase> func)
{
	m_MouseMiddleClickedfunc.push_back(func);
}
void SFMLGUIElement::addMouseRolloverFunction(std::shared_ptr<TFunctorBase> func)
{
	m_MouseRolloverfunc.push_back(func);
}

void SFMLGUIElement::removeMouseLeftPressedFunction(TFunctorBase& func)
{
	std::vector<std::shared_ptr<TFunctorBase>>::iterator it(getFunctionVectorIterator(m_MouseLeftPressedfunc,func));
	if(it != m_MouseLeftPressedfunc.end())
	{
		m_MouseLeftPressedfunc.erase(it);
	}
}
void SFMLGUIElement::removeMouseLeftReleasedFunction(TFunctorBase& func)
	{
	std::vector<std::shared_ptr<TFunctorBase>>::iterator it(getFunctionVectorIterator(m_MouseLeftReleasedfunc,func));
	if(it != m_MouseLeftReleasedfunc.end())
	{
		m_MouseLeftReleasedfunc.erase(it);
	}
}
void SFMLGUIElement::removeMouseRightPressedFunction(TFunctorBase& func)
{
	std::vector<std::shared_ptr<TFunctorBase>>::iterator it(getFunctionVectorIterator(m_MouseRightPressedfunc,func));
	if(it != m_MouseRightPressedfunc.end())
	{
		m_MouseRightPressedfunc.erase(it);
	}
}
void SFMLGUIElement::removeMouseRightReleasedFunction(TFunctorBase& func)
	{
	std::vector<std::shared_ptr<TFunctorBase>>::iterator it(getFunctionVectorIterator(m_MouseRightReleasedfunc,func));
	if(it != m_MouseRightReleasedfunc.end())
	{
		m_MouseRightReleasedfunc.erase(it);
	}
}
void SFMLGUIElement::removeMouseMiddlePressedFunction(TFunctorBase& func) 
	{
	std::vector<std::shared_ptr<TFunctorBase>>::iterator it(getFunctionVectorIterator(m_MouseMiddlePressedfunc,func));
	if(it != m_MouseMiddlePressedfunc.end())
	{
		m_MouseMiddlePressedfunc.erase(it);
	}
}
void SFMLGUIElement::removeMouseMiddleReleasedFunction(TFunctorBase& func)
	{
	std::vector<std::shared_ptr<TFunctorBase>>::iterator it(getFunctionVectorIterator(m_MouseMiddleReleasedfunc,func));
	if(it != m_MouseMiddleReleasedfunc.end())
	{
		m_MouseMiddleReleasedfunc.erase(it);
	}
}
void SFMLGUIElement::removeMouseLeftClickedFunction(TFunctorBase& func) 
	{
	std::vector<std::shared_ptr<TFunctorBase>>::iterator it(getFunctionVectorIterator(m_MouseLeftClickedfunc,func));
	if(it != m_MouseLeftClickedfunc.end())
	{
		m_MouseLeftClickedfunc.erase(it);
	}
}
void SFMLGUIElement::removeMouseRightClickedFunction(TFunctorBase& func)
	{
	std::vector<std::shared_ptr<TFunctorBase>>::iterator it(getFunctionVectorIterator(m_MouseRightClickedfunc,func));
	if(it != m_MouseRightClickedfunc.end())
	{
		m_MouseRightClickedfunc.erase(it);
	}
}
void SFMLGUIElement::removeMouseMiddleClickedFunction(TFunctorBase& func)
	{
	std::vector<std::shared_ptr<TFunctorBase>>::iterator it(getFunctionVectorIterator(m_MouseMiddleClickedfunc,func));
	if(it != m_MouseMiddleClickedfunc.end())
	{
		m_MouseMiddleClickedfunc.erase(it);
	}
}
void SFMLGUIElement::removeMouseRolloverFunction(TFunctorBase& func)
	{
	std::vector<std::shared_ptr<TFunctorBase>>::iterator it(getFunctionVectorIterator(m_MouseRolloverfunc,func));
	if(it != m_MouseRolloverfunc.end())
	{
		m_MouseRolloverfunc.erase(it);
	}
}

std::vector<std::shared_ptr<TFunctorBase>>::iterator SFMLGUIElement::getFunctionVectorIterator(
		std::vector<std::shared_ptr<TFunctorBase>>& vec, TFunctorBase& func)
{
	return std::find_if(vec.begin(), vec.end(), 
		[&](std::shared_ptr<TFunctorBase> a) {return a->equals(func);});
}