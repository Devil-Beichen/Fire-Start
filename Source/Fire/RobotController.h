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

	//代理
	UFUNCTION()
		void OnPerception(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION(BlueprintPure, Category = RobotController)
		class ARobotShooter* GetRobotShooter();

protected:

	//AI感知组件
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = RobotController)
		UAIPerceptionComponent* AIPerception;

	//黑板
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = RobotController)
		UBlackboardData* Blockboard;

	//行为树
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = RobotController)
		UBehaviorTree* BehaviorTree;
};
