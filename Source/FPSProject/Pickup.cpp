// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

#include "FPSProjectCharacter.h"
#include "Components/SphereComponent.h"


// Sets default values
APickup::APickup()
{
	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(RootComponent);
	
	_Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	_Collider->SetupAttachment(_Mesh);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	_Collider->OnComponentBeginOverlap.AddUniqueDynamic(this,&APickup::PickupCoin);
}

void APickup::PickupCoin(UPrimitiveComponent* OverlappedComponent,	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,	const FHitResult& SweepResult)
{
	if(AFPSProjectCharacter* Player = Cast<AFPSProjectCharacter>(OtherActor))
	{
		OnCoinPickedUp.Broadcast(Player->Controller,Score);
		Destroy();
	}
}

