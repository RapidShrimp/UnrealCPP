// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSProjectCharacter.h"

#include "HealthComponent.h"
#include "InteractComp.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AFPSProjectCharacter::AFPSProjectCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
	DefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	
	_HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HeatlhComp"));
	_InteractComp = CreateDefaultSubobject<UInteractComp>(TEXT("InteractComp"));
}

void AFPSProjectCharacter::BeginPlay()
{
	Super::BeginPlay();
	OnDashUpdate.Broadcast(CurrentDashes, _Dashes);
}

void AFPSProjectCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AFPSProjectCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AFPSProjectCharacter::SprintStart()
{
	if(!bIsCrouched)
	{
		GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed * 1.2;
		LerpCamFOV(DefaultFieldOfView*1.1,GetFirstPersonCameraComponent()->FieldOfView);
	}
}

void AFPSProjectCharacter::SprintStop()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	LerpCamFOV(DefaultFieldOfView,GetFirstPersonCameraComponent()->FieldOfView);
}

void AFPSProjectCharacter::StartCrouch()
{
	SprintStop();
	Crouch();
}

void AFPSProjectCharacter::StopCrouch()
{
	UnCrouch();
}

void AFPSProjectCharacter::Slide()
{
	UE_LOG(LogTemp,Error,TEXT("Sliding"));
}

void AFPSProjectCharacter::Dash()
{
	if(CurrentDashes <= 0)
		return;

	FVector Speed = GetActorForwardVector();
	Speed.Normalize(0.01f);
	Speed.Z = 0;
	LaunchCharacter(Speed * _DashForce,true,false);
	CurrentDashes-=1;
	OnDashUpdate.Broadcast(CurrentDashes,_Dashes);
}

void AFPSProjectCharacter::DashRecharge()
{
	CurrentDashes++;
	OnDashUpdate.Broadcast(CurrentDashes,_Dashes);
	if(CurrentDashes >= _Dashes)
	{
		GetWorldTimerManager().ClearTimer(_DashTimer);
		_DashTimer.Invalidate();
		CurrentDashes = _Dashes;
	}
}

void AFPSProjectCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	if(!_DashTimer.IsValid() && _Dashes > CurrentDashes)
	{
		GetWorld()->GetTimerManager().SetTimer(_DashTimer,this,&AFPSProjectCharacter::DashRecharge,_DashChargeRate,true);
	}
}





void AFPSProjectCharacter::Interact()
{
	if(_InteractComp != nullptr)
	{
		_InteractComp->Interact();
	}
}





void AFPSProjectCharacter::SetRifle(bool bNewHasRifle, AWeapon* Weapon)
{
	if(!bHasRifle)
	{
		MyWeapon = Weapon;
	}
	bHasRifle = bNewHasRifle;
}

bool AFPSProjectCharacter::GetHasRifle()
{
	return bHasRifle;
}

void AFPSProjectCharacter::UseWeapon()
{
	if(bHasRifle && UKismetSystemLibrary::DoesImplementInterface(MyWeapon,UFireable::StaticClass()))
	{
		IFireable::Execute_Fire(MyWeapon);
	}
}

void AFPSProjectCharacter::ReloadWeapon()
{
	if(bHasRifle && UKismetSystemLibrary::DoesImplementInterface(MyWeapon,UFireable::StaticClass()))
	{
		IFireable::Execute_Reload(MyWeapon);
	}
}