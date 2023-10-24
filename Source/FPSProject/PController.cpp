// Fill out your copyright notice in the Description page of Project Settings.


#include "PController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FPSProjectCharacter.h"
#include "Kismet/GameplayStatics.h"

void APController::SetupInputComponent()
{
	Super::SetupInputComponent();
	MyPlayerCharacter = Cast<AFPSProjectCharacter>(this->GetPawn());
	if(MyPlayerCharacter != nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("Found Controlled Player Pawn"));
		
		if(UEnhancedInputComponent* EIP = CastChecked<UEnhancedInputComponent>(InputComponent))
		{
			EIP->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APController::CallJumpingStart);
			EIP->BindAction(JumpAction, ETriggerEvent::Completed, this, &APController::CallJumpingEnd);
		
			//Moving
			EIP->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APController::CallMove);
		
			EIP->BindAction(SprintAction,ETriggerEvent::Triggered, this , &APController::CallSprintStart);
			EIP->BindAction(SprintAction,ETriggerEvent::Completed, this , &APController::CallSprintEnd);
		
			EIP->BindAction(CrouchAction,ETriggerEvent::Triggered,this,&APController::CallCrouchStart);
			EIP->BindAction(CrouchAction,ETriggerEvent::Completed,this,&APController::CallCrouchEnd);

			EIP->BindAction(DashAction,ETriggerEvent::Completed,this,&APController::CallDash);

			//Looking
			EIP->BindAction(LookAction, ETriggerEvent::Triggered, this, &APController::CallLook);
		}
	}
}

void APController::BeginPlay()
{
	Super::BeginPlay();
	SetupInputComponent();
		//Adding Mapping Context & Subsystem
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
}

void APController::AddWeaponMappings(UInputMappingContext* InFireMappingContext)
{
	if(MyPlayerCharacter != nullptr)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InFireMappingContext, 1);
			FireMappingContext = InFireMappingContext;
		}
		if(UEnhancedInputComponent* EIP = CastChecked<UEnhancedInputComponent>(InputComponent))
		{
			EIP->BindAction(FireAction,ETriggerEvent::Triggered,this,&APController::CallFireStart);
			EIP->BindAction(ReloadAction,ETriggerEvent::Triggered,this,&APController::CallReload);
			UE_LOG(LogTemp,Warning,TEXT("Successful Binding"))
		}
	}
}

void APController::RemoveWeaponMappings()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
	{
		Subsystem->RemoveMappingContext(FireMappingContext);
		FireMappingContext = nullptr;
	}
	if(UEnhancedInputComponent* EIP = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
	}
}

void APController::CallMove(const FInputActionValue& Value) {MyPlayerCharacter->Move(Value);}
void APController::CallLook(const FInputActionValue& Value) {MyPlayerCharacter->Look(Value);}
void APController::CallSprintStart() {MyPlayerCharacter->SprintStart();}
void APController::CallSprintEnd() {MyPlayerCharacter->SprintStop();}
void APController::CallCrouchStart() {MyPlayerCharacter->StartCrouch();}
void APController::CallCrouchEnd() {MyPlayerCharacter->StopCrouch();}
void APController::CallJumpingStart() {MyPlayerCharacter->Jump();}
void APController::CallJumpingEnd() {MyPlayerCharacter->StopJumping();}
void APController::CallDash() {MyPlayerCharacter->Dash();}

void APController::CallInteract() {MyPlayerCharacter->Interact();}


void APController::CallFireStart() {MyPlayerCharacter->UseWeapon();}
void APController::CallReload() {MyPlayerCharacter->ReloadWeapon();}







