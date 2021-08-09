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

	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent *Mesh1P;

public:
	APlayerShooter();

	// Called to bind functionality to input//绑定函数声明
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
protected:
	
	//声明一个相机组件
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category = Camera)
	UCameraComponent* CameraComponent;

	//前后移动声明
	void MoveForward(float Value);
	
	//左右移动声明
	void MoveRight(float Value);
	
	//左右看声明
	void TurnAtRate(float Rate);
	
	//上下看声明
	void LookUpAtRate(float Rate);
};
