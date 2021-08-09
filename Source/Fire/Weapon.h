// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"


class Shooter;
UCLASS()
class FIRE_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
protected:

	//骨骼网格体的声明
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category=Weapon)
	USkeletalMeshComponent* Mesh;

	//箭头的声明
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category=Weapon)
	class UArrowComponent* Muzzle;


};
