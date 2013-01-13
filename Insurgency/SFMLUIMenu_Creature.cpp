#include "StdAfx.h"
#include "SFMLUIMenu_Creature.h"


SFMLUIMenu_Creature::SFMLUIMenu_Creature(const sf::Window& window, GameTurnTimer& turnTimer, Creature* creature)
	:SFMLUIMenu(window),
	m_rectangle(sf::Vector2f(20.0f*8.0f,20.0f*12.0f)),
	m_equippedItem(),
	m_creature(creature)
{
	m_UIMenu.reset(new UIMenu_Creature(turnTimer, *creature));
	m_helpTextBox.setPosition(0,300);

	m_equippedItem.setPosition(400.0f,0.0f);

	updateMenus();
}


SFMLUIMenu_Creature::~SFMLUIMenu_Creature(void)
{
}

void SFMLUIMenu_Creature::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	SFMLUIMenu::draw(target, states);
	target.draw(m_equippedItem, states);
}
sf::FloatRect SFMLUIMenu_Creature::getLocalBounds(void) const
{
	return m_rectangle.getLocalBounds();
}
sf::FloatRect SFMLUIMenu_Creature::getGlobalBounds(void) const
{
	return getTransform().transformRect(m_rectangle.getGlobalBounds());
}

void SFMLUIMenu_Creature::update()
{
	/*
	if(m_creature->getEquipSlotsComponent()->getEquippedEntity())
		m_equippedItem.setString(m_creature->getEquipSlotsComponent()->getEquippedEntity()->getSName());
	else
		m_equippedItem.setString("Nothing Equipped");
		*/
}