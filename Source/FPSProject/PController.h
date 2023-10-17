// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PController.generated.h"

class AFPSProjectCharacter;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class FPSPROJECT_API APController : public APlayerController
{
	GENERATED_BODY()
	
public:
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	/** Sprint Input Action */
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SprintAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "True"))
	TObjectPtr<UInputAction> CrouchAction;
	
	virtual void SetupInputComponent() override;

	void Debug(const FInputActionValue& Value);

protected:
	virtual void BeginPlay() override;

	TObjectPtr<AFPSProjectCharacter> MyPlayerCharacter;
	/*void SprintStart();
	void SprintStop();
	void StartCrouch();
	void StopCrouch();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartJumping();
	void StopJumping();*/
};
