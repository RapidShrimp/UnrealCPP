// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "FPSProjectCharacter.h"
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



void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	_SphereCollider->OnComponentBeginOverlap.AddUniqueDynamic(this,&AWeapon::OnBeginOverlap);
	_SphereCollider->OnComponentEndOverlap.AddUniqueDynamic(this,&AWeapon::OnEndOverlap);
	_CurrentAmmo = StartingAmmo;
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
			PlayerCharacter->AddInteractable(this);
		}
	} 
}

void AWeapon::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex)
{
	if(AFPSProjectCharacter* PlayerCharacter = Cast<AFPSProjectCharacter>(OtherActor))
	{
		PlayerCharacter->RemoveInteractable(this);
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
		OwningCharacter->RemoveInteractable(this);
		PlayerController->AddWeaponMappings(FireMappingContext);
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
		PlayerController->RemoveWeaponMappings(); 
		FDetachmentTransformRules DetatchmentRules(EDetachmentRule::KeepWorld, true);
		DetachFromActor(DetatchmentRules);
		OwningCharacter->SetRifle(false,nullptr);
		FHitResult Hit;
		if(UKismetSystemLibrary::LineTraceSingle(GetWorld(),OwningCharacter->GetActorLocation(),OwningCharacter->GetActorLocation() - FVector {0,0,1000},UEngineTypes::ConvertToTraceType(ECC_Visibility),false,{this},EDrawDebugTrace::Persistent,Hit,true,FLinearColor::Green,FLinearColor::Red))
		{
			SetActorLocation(Hit.Location);
			SetActorRotation(OwningCharacter->GetActorRotation() - FRotator {90,40,0});
		}
		OwningCharacter->AddInteractable(this);
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
	return false;
}

void AWeapon::Interact_Implementation(AActor* Interacting)
{

	if(AFPSProjectCharacter* Player = Cast<AFPSProjectCharacter>(Interacting))
	{
		AttachWeapon(Player);
	}
}


bool AWeapon::Fire_Implementation()
{
	if(_CurrentClip > 0)
	{
		PlayFireAudio();
		_CurrentClip-=1;
		UE_LOG(LogTemp, Warning, TEXT("Current Clip: %d / %d, Current Ammo %d"), _CurrentClip,_MaxClipSize,_CurrentAmmo);
		return  true;
	}
	else
	{
		//Reload Prompt;
	}
	return false;
}

void AWeapon::PlayFireAudio()
{
	if(FireSound!=nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, this->GetActorLocation());
	}
}


