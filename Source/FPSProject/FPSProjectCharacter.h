// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Weapon.h"
#include "FPSProjectCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpdateDashSignature,int,DashesLeft,int,MaxDashes);

class UInteractComp;
class UHealthComponent;
class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
class AWeapon;

UCLASS(config=Game)
class AFPSProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> _HealthComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInteractComp> _InteractComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FirstPersonCameraComponent;
	
public:
	AFPSProjectCharacter();

protected:
	virtual void BeginPlay();

public:
	/** Bool for AnimBP to switch to another animation set */

	UPROPERTY(BlueprintAssignable)
	FUpdateDashSignature OnDashUpdate;

	/** Setter & Getter for bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetRifle(bool bNewHasRifle,AWeapon* Weapon);
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;
	
	TObjectPtr<AWeapon> MyWeapon;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float _DashForce;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int _Dashes = 2;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float _DashChargeRate = 1.0f;
	
	UFUNCTION(BlueprintImplementableEvent, Category = Camera)
		void LerpCamFOV(float DesiredFieldOfView, float CurrentFieldOfView);

public:

	//Movement Functions
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void SprintStart();
	void SprintStop();
	void StartCrouch();
	void StopCrouch();

	void Slide();

	
	void Dash();
	void DashRecharge();
	FTimerHandle _DashTimer;
	int CurrentDashes = _Dashes;


	void Landed(const FHitResult& Hit) override;

	
	void Interact();
	
	//Interface Weapon Calls
	AWeapon* GetWeapon(){return MyWeapon;}
	UInteractComp* GetInteractComp(){return _InteractComp;}
	
	void UseWeapon();
	void ReloadWeapon();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Input);
	float DefaultFieldOfView = 90;
	float DefaultWalkSpeed;

	UHealthComponent* GetHealthComponent() const {return _HealthComponent; }
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	
};

