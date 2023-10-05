// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstObject.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

// Sets default values
AFirstObject::AFirstObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(_Root);

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(_Root);

	_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	_Arrow->SetupAttachment(_Root);

	_RotationComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
	_RotationComp->SetAutoActivate(false);
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

// Called every frame
void AFirstObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

