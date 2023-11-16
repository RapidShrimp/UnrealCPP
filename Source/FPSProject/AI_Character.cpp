// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Character.h"



// Sets default values
AAI_Character::AAI_Character()
{
}

// Called when the game starts or when spawned
void AAI_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAI_Character::SelfDestruct()
{
}

// Called to bind functionality to input
void AAI_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

