// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSProjectCharacter.h"

#include "AITypes.h"
#include "AnimationCoreLibrary.h"
#include "HealthComponent.h"
#include "InteractComp.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TimelineComponent.h"
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
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
	
	DefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HeatlhComp"));
	InteractComp = CreateDefaultSubobject<UInteractComp>(TEXT("InteractComp"));
}

void AFPSProjectCharacter::BeginPlay()
{
	FOnTimelineFloat  OnTimelineFloat;
	FOnTimelineEventStatic OnTimelineEventStatic;
	Super::BeginPlay();
	WallJumpsLeft = WallJumps;
	DefaultHeight = GetDefaultHalfHeight();
	OnDashUpdate.Broadcast(CurrentDashes, Dashes);


/*
	if (FloatCurve != NULL)
	{
		SlideTimeline = NewObject(this,, FName("SlideTimeline"));
		SlideTimeline->CreationMethod = EComponentCreationMethod::UserConstructionScript; // Indicate it comes from a blueprint so it gets cleared when we rerun construction scripts
		this->BlueprintCreatedComponents.Add(SlideTimeline); // Add to array so it gets saved
		SlideTimeline->SetNetAddressable();    // This component has a stable name that can be referenced for replication

		SlideTimeline->SetPropertySetObject(this); // Set which object the timeline should drive properties on
		SlideTimeline->SetDirectionPropertyName(FName("TimelineDirection"));

		SlideTimeline->SetLooping(false);
		SlideTimeline->SetTimelineLength(5.0f);
		SlideTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);

		SlideTimeline->SetPlaybackPosition(0.0f, false);

		//Add the float curve to the timeline and connect it to your timelines's interpolation function
		OnTimelineFloat.BindUFunction(this, FName{ TEXT("TimelineCallback") });
		OnTimelineEventStatic.BindUFunction(this, FName{ TEXT("TimelineFinishedCallback") });
		SlideTimeline->AddInterpFloat(FloatCurve, OnTimelineFloat);
		SlideTimeline->SetTimelineFinishedFunc(OnTimelineEventStatic);

		SlideTimeline->RegisterComponent();
	}
*/
}


void AFPSProjectCharacter::LowerMultiplier()
{
	SlideForceMultiplier -= 0.1f;
	if(SlideForceMultiplier <= 0)
	{
		CancelSlide();
		SlideForceMultiplier = 0;
		GetWorldTimerManager().ClearTimer(SlideDecrease);
	}
}

void AFPSProjectCharacter::Move(const FInputActionValue& Value)
{
	if(bMovementLocked)
		return;
	
	FVector2D MovementVector = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);
}

void AFPSProjectCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
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

void AFPSProjectCharacter::StartCrouch_Implementation()
{
	if(PlayerCanSlide())
	{
		bIsSliding = true;
		SlideForceMultiplier = 1;
		GetCharacterMovement()->GroundFriction = 0;
		GetCharacterMovement()->BrakingDecelerationWalking = 3000;
	}

	Crouch();
	SprintStop();
	GetCharacterMovement()-> MaxWalkSpeed *= 0.6;
}

void AFPSProjectCharacter::StopCrouch_Implementation()
{
	if(bIsSliding)
		CancelSlide();
	UnCrouch();
	GetCharacterMovement()-> MaxWalkSpeed = DefaultWalkSpeed;
}

void AFPSProjectCharacter::CancelSlide()
{
	bIsSliding = false;
	StopCrouch();
}

FVector AFPSProjectCharacter::CalculateFloorInfluence(const FVector FloorNormal)
{
	FVector FloorDownAngle = FVector::CrossProduct(FloorNormal, FVector::CrossProduct(FloorNormal,FVector::UpVector));
	FloorDownAngle.Normalize();
	return FloorDownAngle;
}

void AFPSProjectCharacter::ApplySlideForce()
{
	if(!bIsSliding)
		return;
	
	FVector FloorInfluence = CalculateFloorInfluence(GetCharacterMovement()->CurrentFloor.HitResult.Normal);
	UE_LOG(LogTemp,Warning,TEXT("Slide-Floor Influence (Normalized)\n %s"),*FloorInfluence.ToString())

	if(FloorInfluence != FVector::ZeroVector && PlayerCanSlide())
	{
		
		GetCharacterMovement()->AddForce(FloorInfluence * SlideForce * SlideForceMultiplier);
		SlideForceMultiplier = 1;
		
	}
	else
	{
		if(!SlideDecrease.IsValid())
			GetWorld()->GetTimerManager().SetTimer(SlideDecrease,this,&AFPSProjectCharacter::LowerMultiplier,0.05,true);
		FVector SlideDir = GetActorForwardVector();
		SlideDir.Normalize();
		GetCharacterMovement()->AddForce(SlideDir*SlideForce*SlideForceMultiplier);
		//StartDecreasing Multiplier
	}
}


bool AFPSProjectCharacter::PlayerCanSlide()
{
	/*if(FloorAngle>MinFallAngle && Player Looking within 45Deg of FloorInfluence && Player Direction is not moving away from influence
	OR
	(floorFlat && ForwardSpeed < MinSlideSpeed))
	AND
	Is Not Falling */
	/*bool const SlopeSteepEnough = FMath::RadiansToDegrees(FVector::DotProduct(FloorDir,FVector::UpVector)) < MinSlopeAngle*-1;
	bool const ActorLookingTowardsInfluence = FVector::DotProduct(GetActorForwardVector(),FloorDir) > 0.5;
	bool const ActorMovingTowardsInfluence = FVector::DotProduct(PlayerDirection,FloorDir) > 0.5f;
	bool const ActorStandingStill = GetCharacterMovement()->Velocity == FVector::ZeroVector;
	bool const SpeedThresholdMet = FVector::DotProduct(GetVelocity(),GetActorForwardVector()) > MinSlideSpeed;
	bool const FloorIsFlat = FloorDir == FVector::ZeroVector;
	*/

	FVector FloorDir = CalculateFloorInfluence(GetCharacterMovement()->CurrentFloor.HitResult.Normal);
	FVector PlayerDirection = GetCharacterMovement()->Velocity;
	PlayerDirection.Normalize();
	
	bool const FloorSpeedCheck = FVector::DotProduct(GetVelocity(),GetActorForwardVector()) > MinSlideSpeed && FloorDir == FVector::ZeroVector;
	bool const SlopeCheck = FMath::RadiansToDegrees(FVector::DotProduct(FloorDir,FVector::UpVector)) < MinSlopeAngle*-1 && FVector::DotProduct(GetActorForwardVector(),FloorDir) > 0.5 && (FVector::DotProduct(PlayerDirection,FloorDir) > 0.5f || GetCharacterMovement()->Velocity == FVector::ZeroVector);

	if(GetCharacterMovement()->IsFalling())
		return false;
	if(SlopeCheck || FloorSpeedCheck)
			return true;
	return false;
}

void AFPSProjectCharacter::Dash()
{
	if(bMovementLocked || CurrentDashes <= 0)
		return;
	
	FVector Speed = GetActorForwardVector();
	Speed.Normalize(0.01f);
	Speed.Z = 0;
	LaunchCharacter(Speed * DashForce,true,false);
	CurrentDashes-=1;
	if(DashTimer.IsValid())
		GetWorldTimerManager().ClearTimer(DashTimer);
	GetWorld()->GetTimerManager().SetTimer(DashTimer,this,&AFPSProjectCharacter::DashRecharge,DashChargeRate,true);
	
	OnDashUpdate.Broadcast(CurrentDashes,Dashes);
}

void AFPSProjectCharacter::DashRecharge()
{
	CurrentDashes++;
	OnDashUpdate.Broadcast(CurrentDashes,Dashes);
	if(CurrentDashes >= Dashes)
	{
		GetWorldTimerManager().ClearTimer(DashTimer);
		DashTimer.Invalidate();
		CurrentDashes = Dashes;
	}
}



void AFPSProjectCharacter::WallRun()
{

	/*			-Wall Checks Conditions-
	 * 0-BothWalls Not Hit -> GTFO of the function & Set Current Wall False
	 * 1-RightWall Not Hit -> Must Be Left
	 * 2-LeftWall Not Hit -> Must Be Right
	 * 3-Both Walls Hit -> Get the Closest
	 * 
	 * 4-Is Desired the Current Wall
	 *		4a Is Wall Forward Vec same?
	 *		4 YES -> return
	 *		4 No -> Rotate Player
	 */
	
	if(!PlayerCanWallRide())
		return;
	
	FHitResult L_Wall = CheckWallInDirection(false);
	FHitResult R_Wall = CheckWallInDirection(true);
	FHitResult DesiredWall;

	
	
	if(!L_Wall.bBlockingHit && !R_Wall.bBlockingHit) //*-0-* 
	{
		CurrentWall = DesiredWall;
		DetachFromWall(false);
		return;
	} 
	
	if(R_Wall.Distance == 0)				//*-1-*
		DesiredWall = L_Wall;
	else if(L_Wall.Distance == 0)			//*-2-*
		DesiredWall = R_Wall;
	else									//*-3-*
		L_Wall.Distance < R_Wall.Distance ? DesiredWall = L_Wall : DesiredWall = R_Wall;

	if(!DesiredWall.GetActor()->ActorHasTag("WallRun"))
	{
		DetachFromWall(false);
		return;
	}
	
	if(DesiredWall.GetActor()==R_Wall.GetActor())
		bRightWall = true;
	else
		bRightWall = false;

	
	if(DesiredWall.GetActor() == CurrentWall.GetActor())
	{
		PlayerGrabWall(DesiredWall);
		RotateTowardsForward(GetWallForwardVector(DesiredWall));
	}
	else
		PlayerGrabWall(DesiredWall);
}

bool AFPSProjectCharacter::PlayerCanWallRide()
{
	//Is Falling & Has Wall Jumps -> return true
	if(bIsOnWall)
		return true;
	PlayerSpeed = FVector::DotProduct(GetVelocity(),GetActorForwardVector());
	if(!GetMovementComponent()->IsFalling()|| WallJumpsLeft <= 0||PlayerSpeed < PlayerMinWallRunSpeed) 
		return false;
	return true;
}




FHitResult AFPSProjectCharacter::CheckWallInDirection(bool CheckRightWall)
{
	FVector Direction;
	if(CheckRightWall)
		Direction = GetActorRightVector();
	else
		Direction = GetActorRightVector()*-1;

	FHitResult WallHit;
	FVector StartLoc = GetActorLocation();
	UKismetSystemLibrary::LineTraceSingle(
	GetWorld(),
	StartLoc,
	StartLoc+Direction *120.0f,
	UEngineTypes::ConvertToTraceType(ECC_Visibility),
	true,
	{},
	EDrawDebugTrace::None,
	WallHit,
	true,
	FLinearColor::Red,
	FLinearColor::Green,
	5);
	return WallHit;
}

bool AFPSProjectCharacter::PlayerGrabWall(FHitResult Wall)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if(!PlayerController)
		return false;
	
	if (!bIsOnWall)
	{
		//Player Movement Functions
		GetCharacterMovement()->GravityScale = WallRunGravityScale;
		if(GetCharacterMovement()->Velocity.Z> 0)
			GetCharacterMovement()->Velocity.Z /= 2;
		else
			GetCharacterMovement()->Velocity.Z = 0;
		bIsOnWall = true;
		WallTilt(bRightWall);
	}
	
	bMovementLocked = true;
	CurrentWall = Wall;
	RotateTowardsForward(GetWallForwardVector(Wall));
	//Camera Functions
	PlayerController->PlayerCameraManager->ViewYawMax =  GetActorRotation().Yaw + 30;
	PlayerController->PlayerCameraManager->ViewYawMin = GetActorRotation().Yaw -30;
	return true;
}

FVector AFPSProjectCharacter::GetWallForwardVector(FHitResult Wall)
{
	

	//Forward
	FVector ForwardDir = FVector::CrossProduct(Wall.Normal, FVector::DownVector * ((bRightWall) ? 1 : -1));
	//DrawDebugLine(GetWorld(),Wall.ImpactPoint,Wall.ImpactPoint + ForwardDir * 50,FColor::Purple,true,10,0,4);
	return ForwardDir;

	/*
	-------------------[Debug For Line Traces (May need these later)]-------------------------------------

	UE_LOG(LogTemp,Warning,TEXT("Rotation = %s"),*ForwardDir.Rotation().ToString());
	//Wall Normal
	DrawDebugLine(GetWorld(),Wall.ImpactPoint,Wall.ImpactPoint + Wall.Normal * 50,FColor::Green,true,10,0,4);
	
	//Back
	FVector BackDir =  Wall.Normal.Rotation().Quaternion().GetRightVector();
	DrawDebugLine(GetWorld(),Wall.ImpactPoint,Wall.ImpactPoint + BackDir * 50,FColor::Red,false,10,0,4);

	//Up
	FVector UpDir =  Wall.Normal.Rotation().Quaternion().GetUpVector();
	DrawDebugLine(GetWorld(),Wall.ImpactPoint,Wall.ImpactPoint + UpDir * 50,FColor::Blue,false,10,0,4);

	//Player
	FVector PlayerRot = Wall.ImpactPoint + GetActorForwardVector() * 50;
	DrawDebugLine(GetWorld(),Wall.ImpactPoint, Wall.ImpactPoint + GetActorForwardVector() *50,FColor::Yellow,false,10,0,4);
	-------------------------------------------------------------------------------------------------------
	*/
}

void AFPSProjectCharacter::DetachFromWall(bool bWallJump)
{
	if(!bIsOnWall)
		return;
	bMovementLocked = false;
	bIsOnWall = false;
	if(WallJumpsLeft > 0 && bWallJump)
	{
		FVector Speed = GetActorForwardVector();
		bRightWall ? Speed = GetActorRightVector() *-1 : Speed = GetActorRightVector();
		Speed.Normalize(0.01f);
		Speed.X *= WallJumpDistance;
		Speed.Y *= WallJumpDistance;
		Speed.Z = WallJumpHeight;
		LaunchCharacter(Speed,false,true);
		WallJumpsLeft--;
	}

	GetCharacterMovement()->GravityScale = 1;

	//Reset Camera to the Defaults
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if(!PlayerController)
		return;
	PlayerController->PlayerCameraManager->ViewYawMin = 0;
	PlayerController->PlayerCameraManager->ViewYawMax =359.998993;
	CancelWallTilt();
}

void AFPSProjectCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	ApplySlideForce();
}


void AFPSProjectCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	DetachFromWall(false);
	WallJumpsLeft = WallJumps;
}

void AFPSProjectCharacter::Interact() const
{
	if(InteractComp != nullptr)
		InteractComp->Interact();
}

void AFPSProjectCharacter::SetRifle(bool bNewHasRifle, AWeapon* Weapon)
{
	MyWeapon = Weapon;
	bHasRifle = bNewHasRifle;
}

bool AFPSProjectCharacter::GetHasRifle()
{
	return bHasRifle;
}

void AFPSProjectCharacter::UseWeapon() const
{
	if(bHasRifle && UKismetSystemLibrary::DoesImplementInterface(MyWeapon,UFireable::StaticClass()))
		IFireable::Execute_Fire(MyWeapon);
}

void AFPSProjectCharacter::ReloadWeapon() const
{
	if(bHasRifle && UKismetSystemLibrary::DoesImplementInterface(MyWeapon,UFireable::StaticClass()))
		IFireable::Execute_Reload(MyWeapon);
}
