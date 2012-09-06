#include "stdafx.h"
#include "EntityComponent.h"

EntityComponent::EntityComponent(EntityComponentID::E lType)
		:m_type(lType)
{
}

EntityComponent::~EntityComponent()
{
}

EntityComponentID::E EntityComponent::getType()
{
	return m_type;
}