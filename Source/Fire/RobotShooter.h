// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shooter.h"
#include "RobotShooter.generated.h"

/**
 *
 */
UCLASS()
class FIRE_API ARobotShooter : public AShooter
{
	GENERATED_BODY()

public:
	ARobotShooter();

	FVector GetShootLocation() override { return this->GetActorLocation(); }

	FVector GetShootDirection() override { return this->GetActorForwardVector(); }
};
