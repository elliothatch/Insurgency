#include "StdAfx.h"
#include "SFMLButton.h"


SFMLButton::SFMLButton(const sf::Window& window)
	:SFMLGUIElement(window),
	 m_unpressedSprite(sf::Sprite()),
	 m_pressedSprite(sf::Sprite())
{
}

SFMLButton::SFMLButton(const sf::Window& window, sf::Sprite unpressedSprite)
	:SFMLGUIElement(window),
	m_unpressedSprite(unpressedSprite),
	m_pressedSprite(sf::Sprite())
{
}

SFMLButton::SFMLButton(const sf::Window& window, sf::Sprite unpressedSprite, sf::Sprite pressedSprite)
	:SFMLGUIElement(window),
	m_unpressedSprite(unpressedSprite),
	m_pressedSprite(pressedSprite)
{
}

SFMLButton::~SFMLButton(void)
{
}

void SFMLButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	if(m_leftPressed || m_middlePressed || m_rightPressed)
		target.draw(m_pressedSprite, states);
	else
		target.draw(m_unpressedSprite, states);
}

sf::FloatRect SFMLButton::getLocalBounds(void) const
{
	if(m_leftPressed || m_middlePressed || m_rightPressed)
		return m_pressedSprite.getLocalBounds();
	else
		return m_unpressedSprite.getLocalBounds();
}

sf::FloatRect SFMLButton::getGlobalBounds(void) const
{
	if(m_leftPressed || m_middlePressed || m_rightPressed)
		return getTransform().transformRect(m_pressedSprite.getGlobalBounds());
	else
		return getTransform().transformRect(m_unpressedSprite.getGlobalBounds());
}

void SFMLButton::setUnpressedSprite(sf::Sprite sprite)
{
	m_unpressedSprite = sprite;
}

void SFMLButton::setPressedSprite(sf::Sprite sprite)
{
	m_pressedSprite = sprite;
}

sf::Sprite& SFMLButton::getUnpressedSprite(void) const
{
	return const_cast<sf::Sprite&>(m_unpressedSprite);
}

sf::Sprite& SFMLButton::getPressedSprite(void) const
{
	return const_cast<sf::Sprite&>(m_pressedSprite);
}