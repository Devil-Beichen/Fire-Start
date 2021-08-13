// Fill out your copyright notice in the Description page of Project Settings.


#include "Shooter.h"

#include "ShooterGameInstance.h"


// Sets default values
AShooter::AShooter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AShooter::BeginPlay()
{
	Super::BeginPlay();

	InitWeapons();
}

// Called every frame
void AShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//遍历生成方法
void AShooter::InitWeapons()
{
	for (const TSubclassOf<AWeapon> WeaponClass : WeaponClasses)
	{
		if (IsValid(WeaponClass))
		{
			CreateWeapon(WeaponClass);
			Weapons[0]->SetActorHiddenInGame(false);
		}
	}
}

//生成武器
void AShooter::CreateWeapon(const TSubclassOf<AWeapon> WeaponClass)
{
	const FActorSpawnParameters Params;
	AWeapon* Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, Params);
	const FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, true);
	Weapon->AttachToComponent(Mesh1P, Rules, "RightWeapon");
	Weapon->SetWeaponOwner(this);
	Weapons.Add(Weapon);
	Weapon->SetActorHiddenInGame(true);
}


//受到伤害
void AShooter::TakeWeaponDamage( float Damage,  AShooter* Enemy)
{
	if (IsDead())
	{
		return;
	}
	Health -= Damage;
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("受到伤害了"));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Health: %f"), Health));
	if (IsDead())
	{
		Die(Enemy);
	}
}

//死亡
void AShooter::Die(AShooter* Enemy)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("死亡"));
	for (auto Weapon : Weapons)
	{
		Weapon->EndFire();
		Weapon->DestThis();
		
	}
	OnDie();
	const UShooterGameInstance* GameInstance = Cast<UShooterGameInstance>(GetGameInstance());
	GameInstance->OnKillInfoUpdate.Broadcast(Enemy->GetClass()->GetName(),this->GetClass()->GetName(),Enemy->Team,this->Team,
		Enemy->GetCurrentWeapon()->GetIcon());
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &APawn::DetachFromControllerPendingDestroy, 0.1, false);
	FDamageEvent DamageEvent;
	this->TakeWeaponDamage(20, this);
}


void AShooter::OnDie()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("我死了"));
	//throw std::logic_error("The method or operation is not implemented.");
}
