// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSwitch.h"

#include "Activator.h"
#include "HealthComponent.h"
#include "SNegativeActionButton.h"


// Sets default values
ATargetSwitch::ATargetSwitch()
{
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(_Root);

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(_Root);

	_HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
	_Activator = CreateDefaultSubobject<UActivator>(TEXT("ActivatorSwitch"));

}
// Called when the game starts or when spawned
void ATargetSwitch::BeginPlay()
{
	if(_HealthComp)
	{
		_HealthComp->OnHealthComponentDamaged.AddUniqueDynamic(this,&ATargetSwitch::Handle_TargetHit);
	}
	
}

void ATargetSwitch::Handle_TargetHit(float NewHealth, float CurrentHealth, float MaxHealth)
{
	_Activator->CallActivate();
}

// Called every frame
void ATargetSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

