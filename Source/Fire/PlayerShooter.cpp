// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShooter.h"

#include <ThirdParty/openexr/Deploy/OpenEXR-2.3.0/OpenEXR/include/ImfArray.h>
#include <ThirdParty/WebRTC/rev.24472/Include/Win64/VS2015/api/video/video_content_type.h>

#include "../../Plugins/Developer/RiderLink/Source/RD/src/rd_core_cpp/src/main/std/list.h"
#include "Algo/ForEach.h"

APlayerShooter::APlayerShooter()
{
	//创建一个相机，绑定在根骨骼上
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	// 创建一个网格体只是自己可见
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>("CharacterMesh1P");
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh1P->SetupAttachment(CameraComponent);
	Mesh1P->bCastDynamicShadow = false; //false
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(0, -90.0f, 0));
	Mesh1P->SetRelativeLocation(FVector(0, -6, -150));
}

// Called to bind functionality to input 调用绑定的函数
void APlayerShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//前后移动
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerShooter::MoveForward);
	//左右移动
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerShooter::MoveRight);
	//左右看
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	//上下看
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	//PlayerInputComponent->BindAxis("TurnRate", this, &APlayerShooter::TurnAtRate);
	//PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerShooter::LookUpAtRate);

	//起跳
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerShooter::Jump);
	//落下
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerShooter::StopJumping);

	//开火
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerShooter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerShooter::EndFire);
}

void APlayerShooter::OnDie()
{
	UCameraComponent* Camera = CameraComponent;
	FHitResult SweepHitResult;
	Camera->K2_AddLocalOffset(FVector(-400, 0, 0), false, SweepHitResult, false);
	GetMesh()->SetSkeletalMesh(DieMesh);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh1P->SetHiddenInGame(false);
}

//前后移动定义
void APlayerShooter::MoveForward(const float Value)
{
	if (Value != 0.0f)
	{
		//UE_LOG(LogTemp, Warning, TEXT("You message"));
		//GEngine->AddOnScreenDebugMessage(-1,5.0f ,FColor::Red , TEXT("前进后退"));
		this->AddMovementInput(GetActorForwardVector(), Value);
	}
}

//左右移动定义
void APlayerShooter::MoveRight(const float Value)
{
	if (Value != 0.0f)
	{
		this->AddMovementInput(GetActorRightVector(), Value);
	}
}

//左右看定义
void APlayerShooter::TurnAtRate(const float Rate)
{
	if (Rate != 0.0f)
	{
		this->AddControllerYawInput(Rate * 45.0f * GetWorld()->GetDeltaSeconds());
	}
}

//上下看定义
void APlayerShooter::LookUpAtRate(const float Rate)
{
	if (Rate != 0.0f)
	{
		this->AddControllerPitchInput(Rate * 45.0f * GetWorld()->GetDeltaSeconds());
	}
}

void APlayerShooter::StartFire()
{
	GetCurrentWeapon()->StartFire();
}

void APlayerShooter::EndFire()
{
}
