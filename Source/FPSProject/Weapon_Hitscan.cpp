// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Hitscan.h"

#include "FPSProjectCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AWeapon_Hitscan::AWeapon_Hitscan()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AWeapon_Hitscan::Init()
{
	if(_TypeData == nullptr)
		return;
	Super::Init();
	_Range = _TypeData->_Range;
}

bool AWeapon_Hitscan::Fire_Implementation()
{
	if(!Super::Fire_Implementation())
		return false;
	FVector StartLoc = _Arrow->GetComponentLocation();
	FVector EndLoc = StartLoc + GetActorForwardVector()*_TypeData->_Range;
	if(OwningCharacter)
	{
		StartLoc = OwningCharacter->GetFirstPersonCameraComponent()->GetComponentLocation();
		EndLoc = StartLoc + OwningCharacter->GetFirstPersonCameraComponent()->GetForwardVector()* _TypeData->_Range;
	}
	FHitResult Hit;
	if(UKismetSystemLibrary::LineTraceSingle(GetWorld(),StartLoc,EndLoc,
	UEngineTypes::ConvertToTraceType(ECC_Visibility),
	true,{this, GetOwner()},EDrawDebugTrace::ForDuration,
	Hit,true,FLinearColor::Red,FLinearColor::Green, 5.0f))
{
	UGameplayStatics::ApplyDamage(Hit.GetActor(),_Damage,OwningCharacter->GetController(),this,UDamageType::StaticClass());
		return  true;
}
	return false;
}


