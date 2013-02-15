#include "StdAfx.h"
#include "RangedWeaponComponent.h"


RangedWeaponComponent::RangedWeaponComponent(void)
	:EntityComponent(EntityComponentID::RangedWeapon)
{
}


RangedWeaponComponent::~RangedWeaponComponent(void)
{
}

RangedWeaponComponent* RangedWeaponComponent::clone() const
{
	return new RangedWeaponComponent(*this);
}