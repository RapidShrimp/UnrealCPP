// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{

}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	_CurrentHealth = _MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddUniqueDynamic(this, &UHealthComponent::DamageTaken);
	Super::BeginPlay();
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	const float Change = FMath::Min(_CurrentHealth,Damage);
	_CurrentHealth -= Change;
	UE_LOG(LogTemp,Display,TEXT("Damage for %f, %f health remaining"), Change, _CurrentHealth);
	OnHealthComponentDamaged.Broadcast(_CurrentHealth,_MaxHealth,Change);
	if(_CurrentHealth <= 0.0f)
	{
		OnHealthComponentDead.Broadcast(InstigatedBy);
	}
}

