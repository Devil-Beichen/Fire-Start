// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include <Perception/AIPerceptionComponent.h>

//#include "RobotShooter.h"
#include <BehaviorTree/BlackboardData.h>
#include "RobotController.generated.h"

/**
 * 
 */
UCLASS()
class FIRE_API ARobotController : public AAIController
{
	GENERATED_BODY()
public:
	ARobotController();

	void BeginPlay() override;

	UFUNCTION()
	void OnPerception(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION(BlueprintPure, Category = RobotController)
	class ARobotShooter* GetRobotShooter();

protected:
	UAIPerceptionComponent* AIPerception;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category=RobotController)
	UBlackboardData* Blockboard;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category=RobotController)
	UBehaviorTree* BehaviorTree;
};
