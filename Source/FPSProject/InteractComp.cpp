// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractComp.h"

#include "FPSProjectCharacter.h"
#include "InteractableComp.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UInteractComp::UInteractComp()
{
	PrimaryComponentTick.bCanEverTick = true;
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

void UInteractComp::AddInteractable(AActor* InteractionActor)
{
	InteractableList.AddUnique(InteractionActor);
	GetWorld()->GetTimerManager().SetTimer(UpdateTimer,this,&UInteractComp::ShowInteract,0.1f,true);
}

void UInteractComp::RemoveInteractable(AActor* InteractionActor)
{
	InteractableList.Remove(InteractionActor);
	UE_LOG(LogTemp,Warning,TEXT("Removed"))
}

AActor* UInteractComp::GetDesiredInteract()
{
	FVector const StartLoc = OwningCharacter->GetFirstPersonCameraComponent()->GetComponentLocation();
	FVector const EndLoc = StartLoc + OwningCharacter->GetFirstPersonCameraComponent()->GetForwardVector() * 400.0f;
	FHitResult Hit;
	UKismetSystemLibrary::LineTraceSingle(GetWorld(),StartLoc,EndLoc,
	UEngineTypes::ConvertToTraceType(ECC_Visibility),false,
	{},EDrawDebugTrace::None,Hit,true,FLinearColor::Blue,FLinearColor::Green);

	float PreviousDistance = 1000;
	AActor* Desired = nullptr;
	for(int i = 0; i < InteractableList.Num(); i++)
	{
		if(FVector::Dist(Hit.Location,InteractableList[i]->GetActorLocation())<PreviousDistance) //Get the distance from hit location to the 
			{
			PreviousDistance = FVector::Dist(Hit.Location,InteractableList[i]->GetActorLocation());
			Desired= InteractableList[i];
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
	AActor* TestActor = GetDesiredInteract();
	if(TestActor == nullptr || TestActor == CurrentSelected)
	{
		OnNoInteract.Broadcast();
		return;
	}
	
	UInteractableComp* Interaction = TestActor->FindComponentByClass<UInteractableComp>();
	if(!Interaction)
		return;
	OnSetInteractPrompt.Broadcast(Interaction->InteractText,Interaction->InteractColour,Interaction->InteractTime);
}

void UInteractComp::Interact()
{
	AActor* Desired = GetDesiredInteract();
	
	if(!Desired)
		return;
	if(UKismetSystemLibrary::DoesImplementInterface(Desired,UInteract::StaticClass()))
		IInteract::Execute_Interact(Desired,GetOwner());
}
