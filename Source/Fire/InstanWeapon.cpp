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
}

void AInstanWeapon::ShootOnce()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("ShootOnce"));
	if (BulletNum <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("呕吼！没子弹了"));
		EndFire();
		return;
	}

	BulletNum--;

	const FVector Start = WeaponOwner->GetShootLocation();
	const FVector End = Start + WeaponOwner->GetShootDirection() * 1500;
	TArray<AActor*> Ignore;
	Ignore.Add(WeaponOwner);
	FHitResult HitResult;
	const bool HasHit = UKismetSystemLibrary::LineTraceSingle(this, Start, End, TraceTypeQuery2, false, Ignore,
	                                                          EDrawDebugTrace::Persistent, HitResult, true);

	if (!HasHit) //判断是否检测到物体
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("呕吼！致命空枪"));
		EndFire(); //没有检查到物体
		return;
	}
	//将检测到的物体转换成Ashooter
	AShooter* Enemy = Cast<AShooter>(HitResult.Actor);
	//没有检查到对应的物体
	if (Enemy == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("打中障碍物了"));
		EndFire();
		return;
	}
	//判断是否击中了自己人
	if (!WeaponOwner->IsEnemy(Enemy))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("打中了自己人"));
		return;
	}
	//打中了敌人
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("打中目标了"));
	Enemy->TakeWeaponDamage(20.0f, WeaponOwner);

	//return;	
}
