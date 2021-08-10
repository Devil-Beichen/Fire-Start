// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "InstanWeapon.generated.h"

/**
 * 
 */
UCLASS()
class FIRE_API AInstanWeapon : public AWeapon
{
	GENERATED_BODY()
public:
	virtual void StartFire() override;
	virtual void EndFire() override;
	virtual void ShootOnce() override;
	
};
