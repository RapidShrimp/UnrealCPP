// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinPickup.h"

#include "FPSProjectCharacter.h"


// Sets default values
ACoinPickup::ACoinPickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACoinPickup::BeginPlay()
{
	Super::BeginPlay();
}

void ACoinPickup::OnPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AFPSProjectCharacter* Player = Cast<AFPSProjectCharacter>(OtherActor))
	{
		OnCoinPickedUp.Broadcast(Player->Controller,Score);
		Super::OnPickup(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	}
}
