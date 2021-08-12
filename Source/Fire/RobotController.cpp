// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotController.h"
#include "RobotShooter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

ARobotController::ARobotController()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerception");
}

void ARobotController::BeginPlay()
{
	Super::BeginPlay();
	//黑板是否有效
	if (Blockboard != nullptr)
	{
		UBlackboardComponent* Comp;
		UseBlackboard(Blockboard, Comp);
	}
	//行为树是否有效
	if ((BehaviorTree != nullptr))
	{
		RunBehaviorTree(BehaviorTree);
	}

	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ARobotController::OnPerception);
}

void ARobotController::OnPerception(AActor* Actor, FAIStimulus Stimulus)
{
	UBlackboardComponent* Comp = UAIBlueprintHelperLibrary::GetBlackboard(this);
	UObject* Object = Comp->GetValueAsObject("Enemy");
	if (Object != Actor)
	{
		return;
	}
	Comp->SetValueAsBool("CanSeeEnemy", Stimulus.WasSuccessfullySensed());
}

ARobotShooter* ARobotController::GetRobotShooter()
{
	return Cast<ARobotShooter>(GetPawn());
}
