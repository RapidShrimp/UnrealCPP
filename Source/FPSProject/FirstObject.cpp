// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstObject.h"
#include "Components/ArrowComponent.h"
#include "HealthComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

// Sets default values
AFirstObject::AFirstObject()
{
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(_Root);

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(_Root);

	_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	_Arrow->SetupAttachment(_Root);

	_RotationComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
	_RotationComp->SetAutoActivate(false);
	
	_HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void AFirstObject::BeginPlay()
{
	Super::BeginPlay();
}

void AFirstObject::StartRotating()
{
	_RotationComp->Activate();
	DiscoMode();
}

void AFirstObject::AddRotationSpeed()
{
	float Speed = _RotationComp->RotationRate.Yaw += 10;
	if (!bIsFloating && Speed >= 800)
	{
		Float();
		bIsFloating = true;
	}
}