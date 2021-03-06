// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"


class AShooter;
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

	virtual void StartFire()
	{
	}; //virtual虚函数
	virtual void EndFire()
	{
	};

	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void ShootOnce()
	{
	};

	void SetWeaponOwner(AShooter* Shooter) { WeaponOwner = Shooter; }

	virtual void PostInitializeComponents() override;

	UTexture2D* GetIcon() { return Icon; }

	//删除自己
	void DestThis();;
protected:
	//骨骼网格体的声明
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* Mesh;

	//箭头的声明
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Weapon)
	class UArrowComponent* Muzzle;

	class AShooter* WeaponOwner;

	// 弹夹大小
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	int ClipSize;

	// 子弹数量
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	int BulletNum;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Weapon)
	UTexture2D* Icon;
};
