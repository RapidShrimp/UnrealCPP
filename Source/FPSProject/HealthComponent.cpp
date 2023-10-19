// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	_MaxHealth = 100.0f;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	_CurrentHealth = _MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddUniqueDynamic(this, &UHealthComponent::DamageTaken);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	const float Change = FMath::Min(_CurrentHealth,Damage);
	_CurrentHealth -= Change;
	UE_LOG(LogTemp,Display,TEXT("Damage for %f, %f health remaining"), Change, _CurrentHealth);
	OnHealthComponentDamaged.Broadcast(_CurrentHealth,_MaxHealth,Change);
	if(_CurrentHealth == 0.0f){OnHealthComponentDead.Broadcast(InstigatedBy);}
}

