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
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;
	
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
	
	void CallSprintStart();
	void CallSprintEnd();
	void CallCrouchStart();
	void CallCrouchEnd();
	void CallMove(const FInputActionValue& Value);
	void CallLook(const FInputActionValue& Value);
	void CallJumpingStart();
	void CallJumpingEnd();

};
