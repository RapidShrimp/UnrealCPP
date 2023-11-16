// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractComp.h"

#include "FPSProjectCharacter.h"
#include "InteractableComp.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UInteractComp::UInteractComp()
{
}

// Called when the game starts
void UInteractComp::BeginPlay()
{
	Super::BeginPlay();
	if(AFPSProjectCharacter* Player =  Cast<AFPSProjectCharacter>(GetOwner()))
	{
		OwningCharacter = Player;
	}
}

void UInteractComp::AddInteractable(UInteractableComp* Interactable)
{
	InteractableList.AddUnique(Interactable);
	GetWorld()->GetTimerManager().SetTimer(UpdateTimer,this,&UInteractComp::ShowInteract,0.1f,true);
}

void UInteractComp::RemoveInteractable(UInteractableComp* Interactable)
{
	InteractableList.Remove(Interactable);
}

UInteractableComp* UInteractComp::GetDesiredInteract()
{
	FVector StartLoc;
	FVector EndLoc;
	if(OwningCharacter)
	{
		StartLoc = OwningCharacter->GetFirstPersonCameraComponent()->GetComponentLocation();
		EndLoc = StartLoc + OwningCharacter->GetFirstPersonCameraComponent()->GetForwardVector() * 400.0f;
	}
	else
	{
		StartLoc = GetOwner()->GetActorLocation();
		EndLoc = StartLoc + FVector::DownVector * 400.0f;
	}
	
	FHitResult Hit;
	UKismetSystemLibrary::LineTraceSingle(GetWorld(),StartLoc,EndLoc,
	UEngineTypes::ConvertToTraceType(ECC_Visibility),false,
	{},EDrawDebugTrace::None,Hit,true,FLinearColor::Blue,FLinearColor::Green);

	float PreviousDistance = 1000;
	UInteractableComp* Desired = nullptr;
	for(int i = 0; i < InteractableList.Num(); i++)
	{
		float const NewHit = FVector::Dist(Hit.Location,InteractableList[i]->GetOwner()->GetActorLocation());
		if(NewHit<PreviousDistance) //Get the distance from hit location to the
		{
			PreviousDistance = NewHit;
			Desired = InteractableList[i];
		} 
	}
	return Desired;
}

void UInteractComp::ShowInteract()
{
	if(InteractableList.Num() == 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(UpdateTimer);
		CurrentSelected = nullptr;
		OnNoInteract.Broadcast();
		return;
	}
	
	UInteractableComp* DesiredInteract = GetDesiredInteract();
	if(DesiredInteract == nullptr)
	{
		OnNoInteract.Broadcast();
		return;
	}

	OnSetInteractPrompt.Broadcast(DesiredInteract->InteractText,DesiredInteract->InteractColour,DesiredInteract->InteractTime);
}

void UInteractComp::Interact()
{
	if(UInteractableComp* InteractableComp = GetDesiredInteract())
	{
		InteractableComp->DoParentInteract(GetOwner());
		RemoveInteractable(InteractableComp);
	}
}
