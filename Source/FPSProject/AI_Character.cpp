// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Character.h"

#include "ChaseAI_Controller.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AAI_Character::AAI_Character()
{
}

// Called when the game starts or when spawned
void AAI_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAI_Character::SelfDestruct()
{
	FVector StartLoc = GetActorLocation();
	float ExplosionRadius = 150.0f;
	TArray<TObjectPtr<AAI_Character>> AI = {};
	TArray<FHitResult> OutHits;
	bool bHit = UKismetSystemLibrary::SphereTraceMulti(
		GetWorld(),
		StartLoc,
		StartLoc,
		ExplosionRadius,
		UEngineTypes::ConvertToTraceType(ECC_Camera),
		false,
		{},
		EDrawDebugTrace::Persistent,
		OutHits,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		5.f);

	if(bHit)
	{
		for (const FHitResult HitResult : OutHits)
		{
			UGameplayStatics::ApplyDamage(HitResult.GetActor(),ExplosionDamage,this->GetController(),this,UDamageType::StaticClass());
		}
	}
	Destroy();
}

// Called to bind functionality to input
void AAI_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

