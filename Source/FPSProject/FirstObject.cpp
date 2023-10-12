// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstObject.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "HealthComponent.h"
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

	_BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	_BoxComponent->SetupAttachment(_Root);

	_HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void AFirstObject::BeginPlay()
{
	Super::BeginPlay();
	_BoxComponent->OnComponentHit.AddUniqueDynamic(this,&AFirstObject::Handle_ComponentHit);
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

// Called every frame
void AFirstObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFirstObject::Handle_ComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(_HealthComponent!=nullptr)
	{
		
	}
}

