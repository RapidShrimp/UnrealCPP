// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSwitch.h"

#include "Activator.h"
#include "HealthComponent.h"


// Sets default values
ATargetSwitch::ATargetSwitch()
{
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(_Root);

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(_Root);
	
	_Activator = CreateDefaultSubobject<UActivator>(TEXT("ActivatorSwitch"));

}
// Called when the game starts or when spawned
void ATargetSwitch::BeginPlay()
{
	OnTakeAnyDamage.AddUniqueDynamic(this,&ATargetSwitch::Handle_TargetHit);
}

void ATargetSwitch::Handle_TargetHit(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	_Activator->CallActivate();
}