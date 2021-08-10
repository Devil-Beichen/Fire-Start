// Fill out your copyright notice in the Description page of Project Settings.


#include "InstanWeapon.h"

void AInstanWeapon::StartFire()
{
	ShootOnce();
}

void AInstanWeapon::EndFire()
{
	
}

void AInstanWeapon::ShootOnce()
{
	
	GEngine->AddOnScreenDebugMessage(-1,5.0f ,FColor::Red , TEXT("ShootOnce"));
}