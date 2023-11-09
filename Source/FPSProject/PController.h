// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WidgetHUD.h"

#include "PController.generated.h"

class AFPSProjectCharacter;
class AWeapon;

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class UWidgetHUD;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> WallRideAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	/** Sprint Input Action */
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SprintAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "True"))
	TObjectPtr<UInputAction> CrouchAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "True"))
	TObjectPtr<UInputAction> SlideAction;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "True"))
	TObjectPtr<UInputAction> DashAction;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "True"))
	TObjectPtr<UInputAction> InteractAction;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "True"))
	TObjectPtr<UInputAction> FireAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "True"))
	TObjectPtr<UInputAction> ReloadAction;
	
	virtual void SetupInputComponent() override;

protected:
	
	virtual void BeginPlay() override;

	TObjectPtr<AFPSProjectCharacter> MyPlayerCharacter;
	
	TObjectPtr<UInputMappingContext> FireMappingContext;
	

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidgetHUD> _HUDWidgetClass;
	TObjectPtr<UWidgetHUD> _HUDWidget;
	
	void CallSprintStart();
	void CallSprintEnd();
	void CallCrouchStart();
	void CallCrouchEnd();
	void CallMove(const FInputActionValue& Value);
	void CallLook(const FInputActionValue& Value);
	void CallJumpingStart();
	void CallJumpingEnd();
	
	void CallDash();
	void CallSlide();
	void CallWallRun();
	void CancelWallRun();
	
	void CallInteract();
	
	void CallFireStart();
	void CallReload();

	UFUNCTION()
	void HandleHealthUpdate(float newHealth,float maxHealth,float healthChange);
	UFUNCTION()
	void HandleAmmoCountersUpdate(int CurrentAmmo,int ClipSize,int CurrentClip);
	UFUNCTION()
	void HandleDashUpdate(int DashesLeft,int MaxDashes);

public:
	void AddWeaponMappings(UInputMappingContext* InFireMappingContext, AWeapon* Weapon);
	void RemoveWeaponMappings(AWeapon* Weapon);

};
