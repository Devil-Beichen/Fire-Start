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

}

// Called every frame
void AShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//遍历生成方法
void AShooter::InitWeapons()
{
	for(const TSubclassOf<AWeapon> WeaponClass:WeaponClasses)
	{
		if(IsValid(WeaponClass) )
		{
			CreateWeapon(WeaponClass);
		}
	}
}

void AShooter::CreateWeapon(const TSubclassOf<AWeapon> WeaponClass)
{
	if(IsValid(WeaponClass))
	{
		const FActorSpawnParameters Params;
		AWeapon*Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass,Params);
		const FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget,true);
		Weapon->AttachToComponent(GetMesh(),Rules ,"RightWeapon");
	}
}

