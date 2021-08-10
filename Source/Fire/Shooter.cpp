// Fill out your copyright notice in the Description page of Project Settings.


#include "Shooter.h"


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
		CreateWeapon(WeaponClass);
		Weapons[0]->SetActorHiddenInGame(false);
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



void AShooter::TakeWeaponDamage(float Damage, AShooter* Enemy)
{
	if (IsDead())
		return;
	Health -= Damage;
	if (IsDead())
		Die();

}

void AShooter::Die()
{
	for (auto Weapon:Weapons)
	{Weapon->EndFire();}
	OnDie();
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &APawn::DetachFromControllerPendingDestroy, 0.1, false);
	FDamageEvent DamageEvent;
	this->TakeWeaponDamage(20,this);
}

void AShooter::OnDie()
{
	//throw std::logic_error("The method or operation is not implemented.");
}
