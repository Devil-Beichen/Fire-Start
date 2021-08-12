// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotShooter.h"


ARobotShooter::ARobotShooter()
{	
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>("CharacterMesh1P");
	Mesh1P->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh1P->SetupAttachment(RootComponent);
	

}
