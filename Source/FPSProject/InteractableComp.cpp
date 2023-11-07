// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableComp.h"

#include "FPSProjectCharacter.h"
#include "IInteract.h"
#include "InteractComp.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UInteractableComp::UInteractableComp()
{

	_Collider = CreateDefaultSubobject<USphereComponent>(TEXT("InteractCollider"));
	_Collider->SetupAttachment(this);
}


void UInteractableComp::BeginPlay()
{
	Super::BeginPlay();
	_Collider->OnComponentBeginOverlap.AddUniqueDynamic(this, &UInteractableComp::OnBeginOverlap);
	_Collider->OnComponentEndOverlap.AddUniqueDynamic(this, &UInteractableComp::OnEndOverlap);
	if(!UKismetSystemLibrary::DoesImplementInterface(GetOwner(),UInteract::StaticClass()))
	{
		UE_LOG(LogTemp,Error,TEXT("Component Attatched to Actor Without Interact Interface %s \n Deleting Component..."), *GetOwner()->GetName());
		DestroyComponent(false);
	}
}

void UInteractableComp::DestroyComponent(bool bPromoteChildren)
{
	_Collider->DestroyComponent();
	Super::DestroyComponent(bPromoteChildren);
}

void UInteractableComp::OnAttachmentChanged()
{
	Super::OnAttachmentChanged();
	_Collider->SetupAttachment(this);
}

void UInteractableComp::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!bCanInteract)
		return;
	
	UInteractComp* InteractorCompTest = Cast<UInteractComp>(OtherActor->GetComponentByClass(UInteractableComp::StaticClass()));
	if(InteractorCompTest!=nullptr)
		UE_LOG(LogTemp,Warning,TEXT("FOUND COMP"));

	
	AFPSProjectCharacter* Player = Cast<AFPSProjectCharacter>(OtherActor);
	if(!Player)
		return;
	UInteractComp* InteractorComp = Player->GetInteractComp();
	if(InteractorComp)
	{
		InteractorComp->AddInteractable(GetOwner());
	}
}

void UInteractableComp::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex)
{
	//UInteractComp* InteractorComp = Cast<UInteractComp>(OtherActor->GetComponentByClass(UInteractableComp::StaticClass()));
	AFPSProjectCharacter* Player = Cast<AFPSProjectCharacter>(OtherActor);
	if(!Player)
		return;
	
	UInteractComp* InteractorComp = Player->GetInteractComp();
	
	if(InteractorComp)
	{
		InteractorComp->RemoveInteractable(GetOwner());
	}
}