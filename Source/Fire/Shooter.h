// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <TimerManager.h>
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

	//声明一个Mesh组件
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh1P;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AWeapon* GetCurrentWeapon() { return Weapons[GetCurrentWeaponIndex]; }

	//生成位置
	virtual FVector GetShootLocation() { return FVector::ZeroVector; }
	//朝向
	virtual FVector GetShootDirection() { return FVector::ZeroVector; }

	bool IsDead() { return Health <= 0; };
	bool IsEnemy(AShooter* Another) { return Team != Another->Team; };

	void TakeWeaponDamage(float Damage, AShooter* Enemy);

protected:
	//遍历生成

	void InitWeapons();
	//单独生成
	void CreateWeapon(TSubclassOf<AWeapon> WeaponClass);

	//武器参数
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Shooter)
	TArray<TSubclassOf<AWeapon>> WeaponClasses;

	TArray<AWeapon*> Weapons;

	int GetCurrentWeaponIndex;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Shooter)
	float Health;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Shooter)
	int Team;

private:
	void Die();
	void OnDie();
};
