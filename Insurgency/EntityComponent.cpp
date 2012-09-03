#include "stdafx.h"
#include "EntityComponent.h"

EntityComponent::EntityComponent(EntityComponentID lType)
		:m_type(lType)
{
}

EntityComponent::~EntityComponent()
{
}

EntityComponentID EntityComponent::getType()
{
	return m_type;
}