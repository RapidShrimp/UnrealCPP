// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

#include "Activator.h"
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
	if(ActivatingActor!=nullptr)
	{
		if(UActivator* Activator = ActivatingActor->GetComponentByClass<UActivator>())
		{
			Activator->OnActivated.AddUniqueDynamic(this,&ADoor::OpenDoor);
			Activator->OnDeactivated.AddUniqueDynamic(this,&ADoor::CloseDoor);
		}
	}
	else
	{
		_Collider->OnComponentBeginOverlap.AddDynamic(this,&ADoor::OnCollBeginOverlap);
		_Collider->OnComponentEndOverlap.AddDynamic(this,&ADoor::OnCollEndOverlap);
	}
	
	StartLocation = _Mesh->GetRelativeLocation();


}

void ADoor::OnCollBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<AFPSProjectCharacter>(OtherActor) && bIsUnlocked)
		OpenDoor(OtherActor);

}

void ADoor::OnCollEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CloseDoor();
}

void ADoor::DoorLock(bool UnLocked)
{
	bIsUnlocked = UnLocked;

	if(bIsUnlocked)
		OpenDoor(nullptr);
	else
		CloseDoor();
}

void ADoor::OpenDoor_Implementation(AActor* Opener)
{
	UE_LOG(LogTemp,Warning,TEXT("DoorOpen"));
}

void ADoor::CloseDoor_Implementation()
{
}


