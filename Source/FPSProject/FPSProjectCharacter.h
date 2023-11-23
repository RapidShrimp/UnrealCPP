// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Weapon.h"
#include "FPSProjectCharacter.generated.h"

class UTimelineComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpdateDashSignature, int, DashesLeft, int, MaxDashes);

class UInteractComp;
class UHealthComponent;
class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
class AWeapon;

UENUM()
enum EMovementType
{
	Walking,
	Sprinting,
	Crouched,
	Sliding
};

UCLASS(config=Game)
class AFPSProjectCharacter : public ACharacter
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInteractComp> InteractComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FirstPersonCameraComponent;

	UPROPERTY()
	TObjectPtr<UTimelineComponent> SlideTimeline;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCurveFloat> FloatCurve;
public:
	AFPSProjectCharacter();
	
	UPROPERTY(BlueprintAssignable)
	FUpdateDashSignature OnDashUpdate;
	
protected:
	virtual void BeginPlay();
	virtual void Landed(const FHitResult& Hit) override;

	//Movement Variables
	bool bMovementLocked = false;
	bool bIsOnWall;
	bool bRightWall;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float CrouchHeight;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float DefaultHeight;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "WallRun")
	float PlayerSpeed;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "WallRun")
	float PlayerMinWallRunSpeed = 520.0f;
	float DefaultWalkSpeed;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "WallRun")
	float WallRunGravityScale = 0.2f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category ="Dash")
	float DashForce = 400;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category ="Dash")
	int Dashes = 2;
	int CurrentDashes = Dashes;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category ="Dash")
	float DashChargeRate = 1.0f;
	FTimerHandle DashTimer;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Camera);
	float DefaultFieldOfView = 90;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "WallRun")
	int WallJumps =3;
	int WallJumpsLeft;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "WallRun")
	float WallJumpHeight = 400;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "WallRun")
	float WallJumpDistance = 600;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "WallRun")
	FHitResult CurrentWall;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Slide")
	float MinSlideSpeed = 600;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Slide")
	float MinSlopeAngle = 10;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Slide")
	float SlideForce = 300000;

	float SlideForceMultiplier = 1;
	bool bIsSliding;
	FTimerHandle SlideDecrease;
	void LowerMultiplier();
	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;
	UPROPERTY()
	TObjectPtr<AWeapon> MyWeapon;
	
public:

	//Movement Functions
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void SprintStart();
	void SprintStop();
	UFUNCTION(BlueprintNativeEvent)
	void StartCrouch();
	UFUNCTION(BlueprintNativeEvent)
	void StopCrouch();

	void StartSlide();
	void CancelSlide();
	void Dash();
	void DashRecharge();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetRifle(bool bNewHasRifle,AWeapon* Weapon);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();
	
	void Interact() const;
	AWeapon* GetWeapon() const {return MyWeapon;}
	void UseWeapon() const;
	void ReloadWeapon() const;

	void WallRun();
	void DetachFromWall(bool bWallJump);

	virtual void Tick(float DeltaSeconds) override;
protected:
	UFUNCTION(BlueprintPure,BlueprintCallable,Category ="Slide")
	bool PlayerCanSlide();
	UFUNCTION(BlueprintPure,BlueprintCallable,Category ="Slide")	
	FVector CalculateFloorInfluence(const FVector FloorNormal);
	void ApplySlideForce();
	FHitResult CheckWallInDirection(bool CheckRightWall);
	bool PlayerGrabWall(FHitResult Wall);
	UFUNCTION(BlueprintPure,BlueprintCallable, Category = "WallRun")
	bool PlayerCanWallRide();
	UFUNCTION(BlueprintPure,BlueprintCallable, Category = "WallRun")
	FVector GetWallForwardVector(FHitResult Wall);
	
	//Camera Functions
	UFUNCTION(BlueprintImplementableEvent, Category = "WallRun")
	void RotateTowardsForward(FVector WallForward);
	UFUNCTION(BlueprintImplementableEvent, Category = Camera)
	void LerpCamFOV(float DesiredFieldOfView, float CurrentFieldOfView);
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable, Category = "WallRun")
	void WallTilt(bool OnRightWall);
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable, Category = "WallRun")
	void CancelWallTilt();

public:	
	UInteractComp* GetInteractComp() const {return InteractComp;}
	UHealthComponent* GetHealthComponent() const {return HealthComponent; }
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};

