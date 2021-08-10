// Fill out your copyright notice in the Description page of Project Settings.


#include "InstanWeapon.h"

#include "Shooter.h"
#include "Kismet/KismetSystemLibrary.h"

void AInstanWeapon::StartFire()
{
	ShootOnce();
}

void AInstanWeapon::EndFire()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("EndFire"));
}

void AInstanWeapon::ShootOnce()
{
//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("ShootOnce"));
	if(BulletNum<=0)
	{
		EndFire();
		return;;
	}
	BulletNum--;
	FVector Start = WeaponOwner->GetShootLocation();
	FVector End = Start + WeaponOwner->GetShootDirection() * 1500;
	TArray<AActor*> Ignore;
	Ignore.Add(WeaponOwner);
	FHitResult HitResult;
	bool HasHit = UKismetSystemLibrary::LineTraceSingle(this, Start, End, TraceTypeQuery2 ,false, Ignore, EDrawDebugTrace::Persistent,HitResult, true);
	if(!HasHit)
	{
		return;
	}
		AShooter*Enemy= Cast<AShooter>(HitResult.Actor);
	if (!WeaponOwner->IsEnemy(Enemy))
	{
		return;
	}
	Enemy->TakeDamage(20.0f,WeaponOwner);
}