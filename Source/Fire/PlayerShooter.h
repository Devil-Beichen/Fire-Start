// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shooter.h"
#include "Camera/CameraComponent.h"
#include "PlayerShooter.generated.h"


/**
 *
 */
UCLASS()
class FIRE_API APlayerShooter : public AShooter
{
	GENERATED_BODY()


public:
	APlayerShooter();

	// Called to bind functionality to input//绑定函数声明
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//从写父类的死亡事件
	virtual void OnDie() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Mesh)
	USkeletalMesh* DieMesh;

protected:
	//声明一个相机组件
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Camera)
	UCameraComponent* CameraComponent;

	//前后移动声明
	void MoveForward(float Value);

	//左右移动声明
	void MoveRight(float Value);

	//左右看声明
	void TurnAtRate(float Rate);

	//上下看声明
	void LookUpAtRate(float Rate);

	//开火声明
	void StartFire();

	//开火结束声明
	void EndFire();

	FVector GetShootLocation() { return CameraComponent->GetComponentLocation(); };

	FVector GetShootDirection() { return CameraComponent->GetForwardVector(); };
};
