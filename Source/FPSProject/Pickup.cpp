// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

#include "Components/SphereComponent.h"


// Sets default values
APickup::APickup()
{
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	_Root->SetupAttachment(RootComponent);
	
	_Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	_Collider->SetupAttachment(_Root);

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(_Collider);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	_Collider->OnComponentBeginOverlap.AddUniqueDynamic(this,&APickup::OnPickup);
}

void APickup::OnPickup(UPrimitiveComponent* OverlappedComponent,	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,	const FHitResult& SweepResult)
{
	Destroy();
}

