// Fill out your copyright notice in the Description page of Project Settings.


#include "PController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FPSProjectCharacter.h"
#include "Kismet/GameplayStatics.h"

void APController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(UEnhancedInputComponent* EIP = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		//Jumping
		EIP->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APController::Debug);

		/*
		 EIP->BindAction(JumpAction, ETriggerEvent::Completed, this, &AFPSProjectCharacter::StopJumping);

		//Moving
		EIP->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPSProjectCharacter::Move);
		
		EIP->BindAction(SprintAction,ETriggerEvent::Triggered, this , &AFPSProjectCharacter::SprintStart);
		EIP->BindAction(SprintAction,ETriggerEvent::Completed, this , &AFPSProjectCharacter::SprintStop);
		
		EIP->BindAction(CrouchAction,ETriggerEvent::Triggered,this,&AFPSProjectCharacter::StartCrouch);
		EIP->BindAction(CrouchAction,ETriggerEvent::Completed,this,&AFPSProjectCharacter::StopCrouch);

		//Looking
		EIP->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPSProjectCharacter::Look);*/
	}
}

void APController::Debug(const FInputActionValue& Value)
{
	UE_LOG(LogTemp,Warning,TEXT("DEBUG PRESS"));
}

void APController::BeginPlay()
{
	Super::BeginPlay();
	
	//Adding Mapping Context & Subsystem
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
}

