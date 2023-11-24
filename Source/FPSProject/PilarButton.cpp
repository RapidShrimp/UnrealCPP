// Fill out your copyright notice in the Description page of Project Settings.


#include "PilarButton.h"

#include "Activator.h"
#include "InteractableComp.h"


// Sets default values
APilarButton::APilarButton()
{
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(_Root);
	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	_Mesh->SetupAttachment(_Root);
	_Activator = CreateDefaultSubobject<UActivator>(TEXT("Activator"));
	_InteractComp= CreateDefaultSubobject<UInteractableComp>(TEXT("Interactable Comp"));
	_InteractComp->SetupAttachment(_Root);
}

void APilarButton::BeginPlay()
{
	Super::BeginPlay();
}

void APilarButton::Interact_Implementation(AActor* Interacting)
{
	IInteract::Interact_Implementation(Interacting);
	_Activator->CallActivate();
}


