// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSProjectCharacter.h"

#include "HealthComponent.h"
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
}

void AFPSProjectCharacter::BeginPlay()
{
	Super::BeginPlay();
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
	UE_LOG(LogTemp,Warning,TEXT("CrouchStart"))
	Crouch();
}

void AFPSProjectCharacter::StopCrouch()
{
	UE_LOG(LogTemp,Warning,TEXT("CrouchEnd"))
	UnCrouch();
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


void AFPSProjectCharacter::AddInteractable(AActor* InterfacedActor)
{
	IInteract* Interfaced = Cast<IInteract>(InterfacedActor);
	if(UKismetSystemLibrary::DoesImplementInterface(InterfacedActor,UInteract::StaticClass()) && Interfaced->GetCanInteract())
	{
		InteractableList.AddUnique(InterfacedActor);
	}
}

void AFPSProjectCharacter::RemoveInteractable(AActor* InterfacedActor)
{
	if(InteractableList.Find(InterfacedActor))
	{
		InteractableList.Remove(InterfacedActor);
	}
}

AActor* AFPSProjectCharacter::GetDesiredInteract()
{
	FVector StartLoc = GetFirstPersonCameraComponent()->GetComponentLocation();
	FVector EndLoc = StartLoc + GetFirstPersonCameraComponent()->GetForwardVector() * 400.0f;
	FHitResult Hit;
	UKismetSystemLibrary::LineTraceSingle(GetWorld(),StartLoc,EndLoc,
	UEngineTypes::ConvertToTraceType(ECC_Visibility),false,
	{},EDrawDebugTrace::None,Hit,true,FLinearColor::Blue,FLinearColor::Green);

	float PreviousDistance = 1000;
	AActor* DesiredInteractalbe = nullptr;
	for(int i = 0; i < InteractableList.Num(); i++)
	{
		if(FVector::Dist(Hit.Location,InteractableList[i]->GetActorLocation())<PreviousDistance) //Get the distance from hit location to the 
		{
			PreviousDistance = FVector::Dist(Hit.Location,InteractableList[i]->GetActorLocation());
			DesiredInteractalbe = InteractableList[i];
		} 
	}
	return DesiredInteractalbe;
}

void AFPSProjectCharacter::Interact()
{
	AActor* Desired = GetDesiredInteract();
	if(Desired != nullptr && UKismetSystemLibrary::DoesImplementInterface(Desired,UInteract::StaticClass()))
	{
		if(GetHasRifle() && UKismetSystemLibrary::DoesImplementInterface(Desired, UFireable::StaticClass()))
		{
			MyWeapon->DropWeapon();
		}
		IInteract::Execute_Interact(Desired,this);
	}
}

void AFPSProjectCharacter::Dash()
{
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
