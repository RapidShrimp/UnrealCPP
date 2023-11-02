// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "FPSProjectCharacter.h"
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
	
	_SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("PickupBox"));
	_SphereCollider->SetupAttachment(_SkeletonMesh);
	_SphereCollider->SetSphereRadius(45.0f);
	
	_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	_Arrow->SetupAttachment(_SkeletonMesh);
	
	_SphereCollider->SetCollisionResponseToAllChannels(ECR_Overlap);
	_SphereCollider->SetSphereRadius(100.0f);
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
	_SphereCollider->OnComponentBeginOverlap.AddUniqueDynamic(this,&AWeapon::OnBeginOverlap);
	_SphereCollider->OnComponentEndOverlap.AddUniqueDynamic(this,&AWeapon::OnEndOverlap);
	SetCanInteract(true);
	Reload_Implementation();
}

void AWeapon::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AFPSProjectCharacter* PlayerCharacter = Cast<AFPSProjectCharacter>(OtherActor))
	{
		if(!PlayerCharacter->GetHasRifle())
			AttachWeapon(PlayerCharacter);
		else if(PlayerCharacter->GetHasRifle())
		{
			PlayerCharacter->GetInteractComp()->AddInteractable(this);
		}
	} 
}

void AWeapon::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex)
{
	if(AFPSProjectCharacter* PlayerCharacter = Cast<AFPSProjectCharacter>(OtherActor))
	{
		PlayerCharacter->GetInteractComp()->RemoveInteractable(this);
	}
}

void AWeapon::AttachWeapon(AFPSProjectCharacter* TargetCharacter)
{
	OwningCharacter = TargetCharacter;
	if (OwningCharacter == nullptr)
	{
		return;
	}
	
	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(OwningCharacter->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));

	//Mapping Rules
	OwningCharacter->SetRifle(true,this);
	if(APController* PlayerController = Cast<APController>(OwningCharacter->GetController()))
	{
		OwningCharacter->GetInteractComp()->RemoveInteractable(this);
		PlayerController->AddWeaponMappings(FireMappingContext,this);
		SetOwner(PlayerController);
		SetInstigator(OwningCharacter);
		OnAmmoCountersUpdate.Broadcast(_CurrentAmmo,_MaxClipSize,_CurrentClip);
	}
	
}

void AWeapon::DropWeapon()
{
	if(OwningCharacter == nullptr)
	{
		return;
	}
	
	if(APController* PlayerController = Cast<APController>(OwningCharacter->GetController()))
	{
		PlayerController->RemoveWeaponMappings(this); 
		FDetachmentTransformRules DetatchmentRules(EDetachmentRule::KeepWorld, true);
		DetachFromActor(DetatchmentRules);
		OwningCharacter->SetRifle(false,nullptr);
		FHitResult Hit;
		if(UKismetSystemLibrary::LineTraceSingle(GetWorld(),OwningCharacter->GetActorLocation(),OwningCharacter->GetActorLocation() - FVector {0,0,1000},UEngineTypes::ConvertToTraceType(ECC_Visibility),false,{this},EDrawDebugTrace::Persistent,Hit,true,FLinearColor::Green,FLinearColor::Red))
		{
			SetActorLocation(Hit.Location);
			SetActorRotation(OwningCharacter->GetActorRotation() - FRotator {90,40,0});
		}
		OwningCharacter->GetInteractComp()->RemoveInteractable(this);
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

void AWeapon::Interact_Implementation(AActor* Interacting)
{

	if(AFPSProjectCharacter* Player = Cast<AFPSProjectCharacter>(Interacting))
	{
		AttachWeapon(Player);
		OnAmmoCountersUpdate.Broadcast(_CurrentAmmo,_MaxClipSize,_CurrentClip);

	}
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
	else
	{
	return false;
	}
}

void AWeapon::PlayFireAudio()
{
	if(_FireSound==nullptr)
	{
		return;
	}
		UGameplayStatics::PlaySoundAtLocation(this, _FireSound, this->GetActorLocation());
}


