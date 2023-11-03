// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableComp.h"
#include "FPSProjectCharacter.h"
#include "InteractComp.h"
#include "Components/SphereComponent.h"


// Sets default values for this component's properties
UInteractableComp::UInteractableComp()
{
	_Collider = CreateDefaultSubobject<USphereComponent>(TEXT("InteractCollider"));
	_Collider->SetupAttachment(GetAttachmentRoot());
	_Collider->SetSphereRadius(100.0f);
}


// Called when the game starts
void UInteractableComp::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractableComp::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AFPSProjectCharacter* PlayerCharacter = Cast<AFPSProjectCharacter>(OtherActor))
	{
		if(PlayerCharacter->GetHasRifle())
		{
			PlayerCharacter->GetInteractComp()->AddInteractable(GetOwner());
		}
	}

}

void UInteractableComp::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex)
{
	if(AFPSProjectCharacter* PlayerCharacter = Cast<AFPSProjectCharacter>(OtherActor))
	{
		PlayerCharacter->GetInteractComp()->RemoveInteractable(GetOwner());
	}
}
