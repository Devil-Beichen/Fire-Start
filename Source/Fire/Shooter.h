// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Weapon.h"
#include "GameFramework/Character.h"
#include "Shooter.generated.h"



UCLASS()
class FIRE_API AShooter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

protected:
	
	//遍历生成
	void InitWeapons();
	//单独生成
	void CreateWeapon(TSubclassOf<AWeapon> WeaponClass);
	
	//武器参数
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category=Shooter)
	TArray<TSubclassOf<AWeapon>> WeaponClasses;

	TArray<AWeapon> Weapons;
};
