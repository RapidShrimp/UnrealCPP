// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

#include "FPSProjectCharacter.h"
#include "Components/BoxComponent.h"


// Sets default values
ADoor::ADoor()
{
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component (Root)"));
	_Root->SetupAttachment(RootComponent);
	
	_Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	_Collider->SetupAttachment(_Root);
	_Collider->SetCollisionResponseToAllChannels(ECR_Overlap);
	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	_Mesh->SetupAttachment(_Root);
}


void ADoor::BeginPlay()
{
	Super::BeginPlay();
	_Collider->OnComponentBeginOverlap.AddUniqueDynamic(this,&ADoor::OnCompBeginOverlap);
	_Collider->OnComponentEndOverlap.AddUniqueDynamic(this,&ADoor::OnCompEndOverlap);
	StartLocation = _Mesh->GetComponentLocation();
}

void ADoor::OnCompBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<AFPSProjectCharacter>(OtherActor) && bIsUnlocked)
		OpenDoor();

}

void ADoor::OnCompEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CloseDoor();
}

void ADoor::DoorLock(bool UnLocked)
{
	bIsUnlocked = UnLocked;

	if(bIsUnlocked)
		OpenDoor();
	else
		CloseDoor();
}

void ADoor::OpenDoor_Implementation()
{
	UE_LOG(LogTemp,Warning,TEXT("DoorOpen"));
}

void ADoor::CloseDoor_Implementation()
{
}


