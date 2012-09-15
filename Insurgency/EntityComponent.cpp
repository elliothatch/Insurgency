#include "stdafx.h"
#include "EntityComponent.h"

EntityComponent::EntityComponent(EntityComponentID::E lType)
		:m_type(lType), m_entity(nullptr)
{
}

EntityComponent::~EntityComponent()
{
}

void EntityComponent::setEntity(GameEntity& lEntity)
{
	m_entity = &lEntity;
}

EntityComponentID::E EntityComponent::getType()
{
	return m_type;
}

GameEntity* EntityComponent::getEntity()
{
	return m_entity;
}