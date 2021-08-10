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
	void StartFire() override;
	void EndFire() override;
	void ShootOnce() override;
	
};
