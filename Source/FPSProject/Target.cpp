// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"

#include "HealthComponent.h"


// Sets default values for this component's properties
UTarget::UTarget()
{
	_PointsValue = 1;
}


// Called when the game starts
void UTarget::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	_HealthComp = Owner->FindComponentByClass<UHealthComponent>();
	if(_HealthComp == nullptr)
	{
		_HealthComp = NewObject<UHealthComponent>(Owner,TEXT("Health"));
		Owner->AddInstanceComponent(_HealthComp);
		_HealthComp->RegisterComponent();
		Owner->Modify();
	}

	Owner->Tags.Add(FName("GameRuleTarget"));
	_HealthComp->OnHealthComponentDead.AddUniqueDynamic(this,&UTarget::Handle_Dead);
}

void UTarget::Handle_Dead(AController* causer)
{
	OnTargetDestroyed.Broadcast(causer,_PointsValue);
	GetOwner()->Destroy();
}


