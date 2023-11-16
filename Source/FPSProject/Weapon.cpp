// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "FPSProjectCharacter.h"
#include "InteractableComp.h"
#include "InteractComp.h"
#include "Components/ArrowComponent.h"

#include "PController.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(_Root);
	
	_SkeletonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	_SkeletonMesh->SetupAttachment(_Root);
	
	_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	_Arrow->SetupAttachment(_SkeletonMesh);

	_InteractableComp = CreateDefaultSubobject<UInteractableComp>(TEXT("Interaction Component"));
	_InteractableComp->SetupAttachment(_SkeletonMesh);
}

void AWeapon::Init()
{
	if(_TypeData == nullptr)
		return;
	_SkeletonMesh->SetSkeletalMesh(_TypeData->_WeaponMesh);
	_FireSound = _TypeData->FireSound;
	_Damage = _TypeData->_Damage;
	_ReloadTime = _TypeData->_ReloadTime;
	_CurrentAmmo = _TypeData->_InitialAmmo;
	_MaxClipSize = _TypeData->_ClipSize;
	_CurrentClip = _MaxClipSize;
}

void AWeapon::BeginPlay()
{
	Init();
	Super::BeginPlay();
}

void AWeapon::Interact_Implementation(AActor* Interacting)
{
	if(AFPSProjectCharacter* Player = Cast<AFPSProjectCharacter>(Interacting))
	{
		if(Player->GetHasRifle())
		{
			Player->GetWeapon()->DropWeapon();
		}
		AttachWeapon(Player);
		UE_LOG(LogTemp,Warning,TEXT("Interacted"))
		
	}
	OnAmmoCountersUpdate.Broadcast(_CurrentAmmo,_MaxClipSize,_CurrentClip);
}

void AWeapon::AttachWeapon(AFPSProjectCharacter* TargetCharacter)
{
	OwningCharacter = TargetCharacter;
	if (OwningCharacter == nullptr)
		return;

	_InteractableComp->SetCanInteract(false);
	OwningCharacter->GetInteractComp()->RemoveInteractable(_InteractableComp);
	
	// Attach the weapon to the First Person Character
	FAttachmentTransformRules const AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(OwningCharacter->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));

	//Mapping Rules
	OwningCharacter->SetRifle(true,this);
	if(APController* PlayerController = Cast<APController>(OwningCharacter->GetController()))
	{
		PlayerController->AddWeaponMappings(FireMappingContext,this);
		SetOwner(PlayerController);
		SetInstigator(OwningCharacter);
		OnAmmoCountersUpdate.Broadcast(_CurrentAmmo,_MaxClipSize,_CurrentClip);
	}
}

void AWeapon::DropWeapon()
{
	if(OwningCharacter == nullptr)
		return;
	
	_InteractableComp->SetCanInteract(true);
	OwningCharacter->GetInteractComp()->AddInteractable(_InteractableComp);

	
	if(APController* PlayerController = Cast<APController>(OwningCharacter->GetController()))
	{
		PlayerController->RemoveWeaponMappings(this); 
		FDetachmentTransformRules  DetatchmentRules(EDetachmentRule::KeepWorld, true);
		DetachFromActor(DetatchmentRules);
		OwningCharacter->SetRifle(false,nullptr);
		FHitResult Hit;
		if(UKismetSystemLibrary::LineTraceSingle(GetWorld(),OwningCharacter->GetActorLocation(),OwningCharacter->GetActorLocation() - FVector {0,0,1000},UEngineTypes::ConvertToTraceType(ECC_Visibility),false,{this},EDrawDebugTrace::None,Hit,true,FLinearColor::Green,FLinearColor::Red))
		{
			SetActorLocation(Hit.Location);
			SetActorRotation(OwningCharacter->GetActorRotation() - FRotator {90,40,0});
		}
		OwningCharacter = nullptr;
	}
}

bool AWeapon::AddAmmo(int InAmmo)
{
	_CurrentAmmo += InAmmo;
	return true;
}
	bool AWeapon::Reload_Implementation()
{
	int AmmoToAdd = _MaxClipSize - _CurrentClip;
	AmmoToAdd = FMath::Min(_CurrentAmmo,AmmoToAdd);
	_CurrentClip += AmmoToAdd;
	_CurrentAmmo -= AmmoToAdd;
	OnAmmoCountersUpdate.Broadcast(_CurrentAmmo,_MaxClipSize,_CurrentClip);
	return false;
}

bool AWeapon::Fire_Implementation()
{
	if(_CurrentClip > 0)
	{
		PlayFireAudio();
		_CurrentClip-=1;
		OnAmmoCountersUpdate.Broadcast(_CurrentAmmo,_MaxClipSize,_CurrentClip);
		return  true;
	}
	return false;
}

void AWeapon::PlayFireAudio()
{
	if(_FireSound==nullptr)
	{
		return;
	}
	UGameplayStatics::PlaySoundAtLocation(this, _FireSound, this->GetActorLocation());
}