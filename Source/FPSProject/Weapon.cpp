// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Components/ArrowComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "FPSProjectCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	_SkeletonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	_SkeletonMesh->SetupAttachment(_Root);
	_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	_Arrow->SetupAttachment(_SkeletonMesh);

}


void AWeapon::AttachWeapon(AFPSProjectCharacter* TargetCharacter)
{
	Character = TargetCharacter;
	if (Character == nullptr)
	{
		return;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
	Character->SetHasRifle(true);

	// Set up action bindings
	if (TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}
		if(UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			EIC->BindAction(FireAction, ETriggerEvent::Triggered, this , &AWeapon::Fire);
		}
	}
}

void AWeapon::DropWeapon(AFPSProjectCharacter* TargetCharacter)
{
	if (TargetCharacter != nullptr)
	{
		//Remove From Parent
		//Disable Input Mapping
		//Disable Input Action
		//Enable Collider
		//Place on Floor
	}
}


bool AWeapon::Fire_Implementation()
{
	return true;
}
