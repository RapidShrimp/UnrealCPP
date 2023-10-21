// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Components/ArrowComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

#include "FPSProjectCharacter.h"
#include "PController.h"

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	_SkeletonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	_SkeletonMesh->SetupAttachment(_Root);
	
	_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	_Arrow->SetupAttachment(_SkeletonMesh);
	
	_SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("PickupBox"));
	_SphereCollider->SetupAttachment(_SkeletonMesh);
	_SphereCollider->SetSphereRadius(45.0f);

}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	_SphereCollider->OnComponentBeginOverlap.AddDynamic(this,&AWeapon::OnOverlap);
}

void AWeapon::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AFPSProjectCharacter* PlayerCharacter = Cast<AFPSProjectCharacter>(OtherActor))
	{
		if(!PlayerCharacter->GetHasRifle())
			AttachWeapon(PlayerCharacter);
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
		PlayerController->AddWeaponMappings(FireMappingContext);
	}
	
}

void AWeapon::DropWeapon()
{
	if(APController* PlayerController = Cast<APController>(OwningCharacter->GetController()))
	{
		PlayerController->RemoveWeaponMappings(FireMappingContext);
		FDetachmentTransformRules DetatchmentRules(EDetachmentRule::KeepWorld, true);
		DetachFromActor(DetatchmentRules);
		OwningCharacter->SetRifle(false,nullptr);
	}
}


bool AWeapon::Fire_Implementation()
{
	DropWeapon();
	UE_LOG(LogTemp,Display,TEXT("FIRING"))
	return true;
}
