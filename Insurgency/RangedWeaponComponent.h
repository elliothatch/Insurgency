#pragma once
#include "EntityComponent.h"

class RangedWeaponComponent : public EntityComponent
{
public:
	RangedWeaponComponent(void);
	virtual ~RangedWeaponComponent(void);

	virtual RangedWeaponComponent* clone() const;
};

