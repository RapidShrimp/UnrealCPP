// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon_Projectile.h"

#include "FPSProjectCharacter.h"
#include "Components/ArrowComponent.h"
#include "FPSProjectProjectile.h"
#include "Camera/CameraComponent.h"


// Sets default values
AWeapon_Projectile::AWeapon_Projectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

bool AWeapon_Projectile::Fire_Implementation()
{
	UWorld* const World = GetWorld();
	if(World == nullptr || !_Projectile) {return false;}
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwner();
	spawnParams.Instigator = GetInstigator();
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	const FTransform TForm = {OwningCharacter->GetFirstPersonCameraComponent()->GetComponentRotation(),_Arrow->GetComponentLocation()};
	World->SpawnActor(_Projectile,&TForm,spawnParams);
	UE_LOG(LogTemp,Warning,TEXT("FIRED PROJECTILE"))
	return Super::Fire_Implementation();
	
}

// Called when the game starts or when spawned
void AWeapon_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}
